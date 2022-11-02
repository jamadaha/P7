#include "WalkerReformulator.hh"

using namespace std;

const int debugIndent = 2;

PDDLInstance WalkerReformulator::ReformulatePDDL(PDDLInstance* instance) {
	// Walk the PDDL
	auto paths = PerformWalk(instance);

	// Find Entangelements
	auto candidates = FindEntanglements(&paths, instance);

	// Generate new Macros
	auto newInstance = GenerateMacros(candidates, instance);

	return newInstance;
}

vector<Path> WalkerReformulator::PerformWalk(PDDLInstance* instance) {
	Walker walker = Walker(instance, ActionGenerator(instance->domain, instance->problem));
	BaseHeuristic *heuristic;
	if (Configs->GetItem<string>("heuristic") == "random")
		heuristic = new RandomHeuristic(Configs->GetItem<bool>("debugmode"));
	else if (Configs->GetItem<string>("heuristic") == "goalCount")
		heuristic = new GoalCountHeuristic(instance->domain, instance->problem);
	else if (Configs->GetItem<string>("heuristic") == "goalPredicateCount")
		heuristic = new GoalPredicateCountHeuristic(instance->domain, instance->problem);
	else
		throw std::invalid_argument("Invalid heuristic specified in config");
	BaseDepthFunction *depthFunc = new ConstantDepthFunction(1000, *instance, 1);
	BaseWidthFunction *widthFunc = new TimeWidthFunction(TimeLimit * 1000);

	if (Configs->GetItem<bool>("debugmode")) {
		ProgressBarHelper* bar;
		walker.OnWalkerStart = [&]() {
			bar = new ProgressBarHelper(widthFunc->max, "Walking", debugIndent + 1);

			if (Configs->GetItem<bool>("printwalkersteps")) {
				std::string command = "truncate -s 0 walkerLog";
				system(command.c_str());
			}
		};
		walker.OnWalkerStep = [&](int currentStep) {
			bar->SetTo(currentStep);
		};
		walker.OnWalkerEnd = [&]() {
			bar->End();
		};
		if (Configs->GetItem<bool>("printwalkersteps")) {
			walker.OnTempStateMade = [&](PDDLInstance* instance, PDDLState* state) {
				std::string command = "echo '" + state->ToString(instance) + "'" + " >> walkerLog";
				system(command.c_str());

			};
			walker.OnStateWalk = [&](PDDLInstance* instance, PDDLState* state, PDDLActionInstance* chosenAction) {
				std::string stateinfo = state->ToString(instance);
				std::string actioninfo = chosenAction->ToString(instance);
				std::string content = "echo '" + actioninfo + "\n" + stateinfo + "'" + " >> walkerLog";

				system(content.c_str());
			};
		}
	}

	//int i = report->Begin("Walking");
	std::vector<Path> paths = walker.Walk(heuristic, depthFunc, widthFunc);
	free(heuristic); free(widthFunc); free(depthFunc);
	//auto ellapsed = report->Stop(i);

	// Print debug info
	if (Configs->GetItem<bool>("debugmode")) {
		unsigned int totalIterations = paths.size();
		unsigned int totalActionCount = walker.GetTotalActionsGenerated();
		//ConsoleHelper::PrintDebugInfo("[Walker] Total walk time:         " + to_string(ellapsed) + "ms", 1);
		//double iterationsPrSecond = (totalIterations * 1000) / (ellapsed + 1);
		//ConsoleHelper::PrintDebugInfo("[Walker] Total walker iterations: " + to_string(totalIterations) + " [" + to_string(iterationsPrSecond) + "/s]", 1);
		//double actionsPrSecond = (totalActionCount * 1000) / (ellapsed + 1);
		//ConsoleHelper::PrintDebugInfo("[Walker] Total actions Generated: " + to_string(totalActionCount) + " [" + to_string(actionsPrSecond) + "/s]", 1);
	}

	return paths;
}

vector<EntanglementOccurance> WalkerReformulator::FindEntanglements(vector<Path>* paths, PDDLInstance* instance) {
	// Find entanglement candidates.
	auto entFinderData = EntanglementFinder::RunData();

	entFinderData.LevelReductionFactor = Configs->GetItem<int>("levelReductionFactor");
	entFinderData.SearchCeiling = Configs->GetItem<int>("searchCeiling");
	entFinderData.SearchFloor = Configs->GetItem<int>("searchFloor");
	if (Configs->GetItem<string>("levelReductionTypes") == "Division")
		entFinderData.LevelReductionType = EntanglementFinder::RunData::Division;
	if (Configs->GetItem<string>("levelReductionTypes") == "Subtraction")
		entFinderData.LevelReductionType = EntanglementFinder::RunData::Subtraction;

	EntanglementFinder entFinder(entFinderData);

	if (Configs->GetItem<bool>("debugmode")) {
		ProgressBarHelper* bar;
		entFinder.OnNewLevel = [&](int level, int outOf) {
			bar = new ProgressBarHelper(outOf, "Finding Entanglements (level " + to_string(level) + ")", debugIndent + 1);
		};
		entFinder.OnLevelIteration = [&](int current, int outOf) {
			bar->Update();
		};
		entFinder.OnLevelEnd = [&]() {
			bar->End();
		};
	}

	//int entangleID = report->Begin("Finding Entanglements");
	auto candidates = entFinder.FindEntangledCandidates(paths);
	//auto ellapsed = report->Stop(entangleID);

	if (Configs->GetItem<bool>("debugmode")) {
		unsigned int totalActions = 0;
		for (int i = 0; i < paths->size(); i++)
			totalActions += paths->at(i).steps.size();

		//ConsoleHelper::PrintDebugInfo("[Entanglement Finder] Total search time:         " + to_string(ellapsed) + "ms", 1);
		ConsoleHelper::PrintDebugInfo("[Entanglement Finder] Total Levels:              " + to_string(entFinder.TotalLevels()), debugIndent);
		//double comparisonsPrSecond = (entFinder.TotalComparisons()) / (ellapsed + 1);
		//ConsoleHelper::PrintDebugInfo("[Entanglement Finder] Total Comparisons:         " + to_string(entFinder.TotalComparisons()) + " [" + to_string(comparisonsPrSecond) + "k/s]", 1);
		ConsoleHelper::PrintDebugInfo("[Entanglement Finder] Total Candidates:          " + to_string(candidates.size()), debugIndent);
		ConsoleHelper::PrintDebugInfo("[Entanglement Finder] Path Data:                 " + to_string(paths->size()) + " paths with " + to_string(totalActions) + " steps in total", debugIndent);
	}

	// Sanitize and remove bad candidates.
	EntanglementEvaluator::RunData entEvaluatorData;
	entEvaluatorData.MinimumOccurancePercent = Configs->GetItem<double>("minimumOccurancePercent");
	entEvaluatorData.MinimumCrossOccurancePercent = Configs->GetItem<double>("minimumCrossOccurancePercent");

	EntanglementEvaluator entEvaluator(entEvaluatorData);
	if (Configs->GetItem<string>("entanglerLengthModifier") == "lengthBias")
		entEvaluator.LengthModifier = EntanglementEvaluatorModifiers::LengthModifiers::LengthBias;

	//int evaluationID = report->Begin("Evaluating Entanglements");
	auto sanitizedCandidates = entEvaluator.EvaluateAndSanitizeCandidates(candidates);
	//ellapsed = report->Stop(evaluationID);

	if (Configs->GetItem<bool>("debugmode")) {
		//ConsoleHelper::PrintDebugInfo("[Entanglement Evaluator] Total evaluation time:  " + to_string(ellapsed) + "ms", 1);
		ConsoleHelper::PrintDebugInfo("[Entanglement Evaluator] Total Candidates:       " + to_string(sanitizedCandidates.size()) + " (" + to_string(entEvaluator.RemovedCandidates()) + " removed)", debugIndent);
	}

	if (Configs->GetItem<bool>("printentanglersteps")) {
		ConsoleHelper::PrintDebugInfo("[Entanglement Evaluator] Top 10 Entanglements:", debugIndent);
		ConsoleHelper::PrintDebugInfo("[Entanglements] Quality  : Chain", debugIndent + 1);
		int counter = 0;
		for (auto i = sanitizedCandidates.begin(); i != sanitizedCandidates.end(); i++) {
			string actionStr = "";
			for (int j = 0; j < (*i).Chain.size(); j++) {
				auto item = (*i).Chain.at(j);
				string paramStr = "";
				for (int l = 0; l < item->objects.size(); l++) {
					paramStr += instance->problem->objects[item->objects[l]];
					if (l != item->objects.size() - 1)
						paramStr += ", ";
				}
				actionStr += item->action->name + "(" + paramStr + ")";
				if (j != (*i).Chain.size() - 1)
					actionStr += " -> ";
			}
			ConsoleHelper::PrintDebugInfo("[Entanglements] " + to_string((*i).Quality) + " : " + actionStr, debugIndent + 1);
			counter++;
			if (counter > 10)
				break;
		}
	}
	
	return sanitizedCandidates;
}

PDDLInstance WalkerReformulator::GenerateMacros(vector<EntanglementOccurance> candidates, PDDLInstance* instance) {
	MacroGenerator macroGenerator = MacroGenerator(instance->domain, instance->problem);

	ProgressBarHelper* bar;
	if (Configs->GetItem<bool>("debugmode")) {
		ConsoleHelper::PrintDebugInfo("[Macro Generator] Generating Macros...", debugIndent);
		bar = new ProgressBarHelper(candidates.size(), "", debugIndent + 1);
	}
	for (int i = 0; i < candidates.size(); i++) {
		macros.push_back(macroGenerator.GenerateMacro(&candidates.at(i).Chain));
		if (Configs->GetItem<bool>("debugmode"))
			bar->Update();
	}
	if (Configs->GetItem<bool>("debugmode"))
		bar->End();

	return InstanceGenerator::GenerateInstance(instance->domain, instance->problem, &macros);
}

SASPlan WalkerReformulator::RebuildSASPlan(PDDLInstance *instance, SASPlan* reformulatedSAS) {
	std::vector<SASAction> actions;
	for (int i = 0; i < reformulatedSAS->actions.size(); i++) {
		auto sasAction = reformulatedSAS->actions.at(i);
		unsigned int actionIndex = -1;
		for (int t = 0; t < instance->domain->actions.size(); t++)
			if (instance->domain->actions.at(t).name == sasAction.name)
				actionIndex = t;
		if (actionIndex != -1) {
			// Untested
			std::vector<std::string> args;
			for (int t = 0; t < sasAction.parameters.size(); t++)
				args.push_back(sasAction.parameters.at(t));
			actions.push_back(SASAction(sasAction.name, args));
		} else {
			for (auto macro : macros) {
				if (sasAction.name == macro.name)
					for (auto macroAction : macro.path) {
						std::vector<std::string> args; args.reserve(macroAction.objects.size());
						for (auto object : macroAction.objects) 
							args.push_back(instance->problem->objects.at(object));
						actions.push_back(SASAction(macroAction.action->name, args));
					}
						
			}
		}
	}
	// Do Something and give a "corrected" SAS plan back
	SASPlan newPlan = SASPlan(actions, actions.size());
	return newPlan;
} 
