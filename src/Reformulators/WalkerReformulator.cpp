#include "WalkerReformulator.hh"

using namespace std;

const int debugIndent = 2;

PDDLInstance WalkerReformulator::ReformulatePDDL(PDDLInstance* instance) {
	// Walk the PDDL
	int walkID = Report->Begin("Walking", ReportID);
	auto newPaths = PerformWalk(instance);
	for (int i = 0; i < newPaths.size(); i++)
		paths.push_back(newPaths.at(i));
	auto ellapsed = Report->Stop(walkID);
	if (Configs->GetItem<bool>("debugmode"))
		PrintWalkerDebugData(ellapsed);

	// Find Entangelements
	int entangleID = Report->Begin("Finding Entanglements", ReportID);
	auto candidates = FindEntanglements(&paths, instance);
	ellapsed = Report->Stop();
	if (Configs->GetItem<bool>("debugmode"))
		PrintEntanglerDebugData(ellapsed, &candidates);
	if (Configs->GetItem<bool>("printentanglersteps"))
		PrintEntanglerSteps(&candidates, instance);

	// Generate new Macros
	int generateMacroID = Report->Begin("Generating Macros", ReportID);
	auto newInstance = GenerateMacros(&candidates, instance);
	ellapsed = Report->Stop(generateMacroID);
	if (Configs->GetItem<bool>("debugmode")) {
		ConsoleHelper::PrintDebugInfo("[Macro Generator] Total generation time:         " + to_string(ellapsed) + "ms", debugIndent);
	}

	free(entanglementFinder);
	free(entanglementEvaluator);
	free(macroGenerator);

	return newInstance;
}

vector<Path> WalkerReformulator::PerformWalk(PDDLInstance* instance) {
	std::vector<BaseWalker*> walkers;
	auto walkerNames = Configs->GetItem<vector<string>>("walkers");
	auto walkerHeuistics = Configs->GetItem<vector<string>>("walkersHeuristic");
	auto walkersTimes = Configs->GetItem<vector<double>>("walkersTimeDistribution");
	for (int i = 0; i < walkerNames.size(); i++) {
		if (walkerNames.at(i) == "walker") {
			BaseHeuristic* heuristic = FindHeuristic(walkerHeuistics.at(i), instance);
			BaseDepthFunction* depthFunc = new ConstantDepthFunction(1000, instance, 1);
			int timeLimit = TimeLimit * walkersTimes.at(i);
			BaseWidthFunction* widthFunc = new TimeWidthFunction(timeLimit);
			BaseWalker *newWalker = new Walker(instance, ActionGenerator(&instance->domain->actions, instance->problem->objects.size()), heuristic, depthFunc, widthFunc);
			walkers.push_back(newWalker);
			if (Configs->GetItem<bool>("debugmode"))
				SetupWalkerDebugInfo(newWalker);
		}
	}

	std::vector<Path> paths;
	for (int i = 0; i < walkers.size(); i++) {
		auto addPaths = walkers.at(i)->Walk();
		paths.insert(paths.end(), addPaths.begin(), addPaths.end());
	}
	
	for (auto w : walkers)
		delete(w);

	return paths;
}

BaseHeuristic* WalkerReformulator::FindHeuristic(string name, PDDLInstance* instance) {
	if (name == "random")
		return new RandomHeuristic(Configs->GetItem<bool>("debugmode"));
	else if (name == "goalCount")
		return new GoalCountHeuristic(instance->domain, instance->problem);
	else if (name == "goalPredicateCount")
		return new GoalPredicateCountHeuristic(instance->domain, instance->problem);
	else if (name == "greedyHeuristic")
		return new GreedyHeuristic(instance->domain, instance->problem);
	else
		throw std::invalid_argument("Invalid heuristic specified in config");
}

void WalkerReformulator::SetupWalkerDebugInfo(BaseWalker* walker) {
	walker->OnWalkerStart = [&](BaseWalker* sender) {
		walkerBar = new ProgressBarHelper(sender->widthFunc->max, "Walking (" + sender->WalkerName + ")", debugIndent + 1);

		if (Configs->GetItem<bool>("printwalkersteps")) {
			std::string command = "truncate -s 0 walkerLog";
			system(command.c_str());
		}
	};
	walker->OnWalkerStep = [&](BaseWalker* sender, int currentStep) {
		walkerBar->SetTo(currentStep);
	};
	walker->OnWalkerEnd = [&](BaseWalker* sender, int timePassed) {
		walkerBar->End();
		unsigned int totalIterations = sender->GetTotalIterations();
		unsigned int totalActionCount = sender->GetTotalActionsGenerated();
		ConsoleHelper::PrintDebugInfo("[Walker] Total walk time:         " + to_string(timePassed) + "ms", debugIndent);
		double iterationsPrSecond = (totalIterations * 1000) / (timePassed + 1);
		ConsoleHelper::PrintDebugInfo("[Walker] Total walker iterations: " + to_string(totalIterations) + " [" + to_string(iterationsPrSecond) + "/s]", debugIndent);
		double actionsPrSecond = (totalActionCount * 1000) / (timePassed + 1);
		ConsoleHelper::PrintDebugInfo("[Walker] Total actions Generated: " + to_string(totalActionCount) + " [" + to_string(actionsPrSecond) + "/s]", debugIndent);
	};
	if (Configs->GetItem<bool>("printwalkersteps")) {
		walker->OnTempStateMade = [&](PDDLInstance* instance, PDDLState* state) {
			std::string command = "echo '" + state->ToString(instance) + "'" + " >> walkerLog";
			system(command.c_str());

		};
		walker->OnStateWalk = [&](PDDLInstance* instance, PDDLState* state, PDDLActionInstance* chosenAction) {
			std::string stateinfo = state->ToString(instance);
			std::string actioninfo = chosenAction->ToString(instance);
			std::string content = "echo '" + actioninfo + "\n" + stateinfo + "'" + " >> walkerLog";

			system(content.c_str());
		};
	}
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

	entanglementFinder = new EntanglementFinder(entFinderData);

	if (Configs->GetItem<bool>("debugmode")) {
		ProgressBarHelper* bar;
		entanglementFinder->OnNewLevel = [&](int level, int outOf) {
			bar = new ProgressBarHelper(outOf, "Finding Entanglements (level " + to_string(level) + ")", debugIndent + 1);
		};
		entanglementFinder->OnLevelIteration = [&](int current, int outOf) {
			bar->Update();
		};
		entanglementFinder->OnLevelEnd = [&]() {
			bar->End();
		};
	}

	auto candidates = entanglementFinder->FindEntangledCandidates(paths);

	// Sanitize and remove bad candidates.
	EntanglementEvaluator::RunData entEvaluatorData;
	entEvaluatorData.MinimumQualityPercent = Configs->GetItem<double>("minimumQualityPercent");
	entEvaluatorData.MaxCandidates = Configs->GetItem<int>("maxCandidates");

	entanglementEvaluator = new EntanglementEvaluator(entEvaluatorData);
	if (Configs->GetItem<string>("entanglerLengthModifier") == "lengthBias")
		entanglementEvaluator->LengthModifier = EntanglementEvaluatorModifiers::LengthModifiers::LengthBias;
	if (Configs->GetItem<string>("entanglerLengthModifier") == "none")
		entanglementEvaluator->LengthModifier = EntanglementEvaluatorModifiers::LengthModifiers::None;

	if (Configs->GetItem<string>("entanglerOccuranceModifier") == "none")
		entanglementEvaluator->OccuranceModifier = EntanglementEvaluatorModifiers::OccuranceModifiers::None;
	if (Configs->GetItem<string>("entanglerOccuranceModifier") == "lowOccuranceBias")
		entanglementEvaluator->OccuranceModifier = EntanglementEvaluatorModifiers::OccuranceModifiers::LowOccuranceBias;


	auto sanitizedCandidates = entanglementEvaluator->EvaluateAndSanitizeCandidates(candidates);
	
	return sanitizedCandidates;
}

PDDLInstance WalkerReformulator::GenerateMacros(vector<EntanglementOccurance>* candidates, PDDLInstance* instance) {
	macroGenerator = new MacroGenerator(instance->domain, instance->problem);
	macros.clear();

	ProgressBarHelper* bar;
	if (Configs->GetItem<bool>("debugmode")) {
		ConsoleHelper::PrintDebugInfo("[Macro Generator] Generating Macros...", debugIndent);
		bar = new ProgressBarHelper(candidates->size(), "", debugIndent + 1);
	}
	for (int i = 0; i < candidates->size(); i++) {
		macros.push_back(macroGenerator->GenerateMacro(&candidates->at(i).Chain));
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

#pragma region Debug Items

void WalkerReformulator::PrintEntanglerSteps(vector<EntanglementOccurance>* candidates, PDDLInstance* instance) {
	ConsoleHelper::PrintDebugInfo("[Entanglement Evaluator] Top 10 Entanglements:", debugIndent);
	ConsoleHelper::PrintDebugInfo("[Entanglements] Quality  : Chain", debugIndent + 1);
	int counter = 0;
	for (auto i = candidates->begin(); i != candidates->end(); i++) {
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

void WalkerReformulator::PrintWalkerDebugData(double ellapsed) {
	ConsoleHelper::PrintDebugInfo("[Walker] Total walk time:         " + to_string(ellapsed) + "ms", debugIndent);
}

void WalkerReformulator::PrintEntanglerDebugData(double ellapsed, vector<EntanglementOccurance>* candidates) {
	unsigned int totalActions = 0;
	for (int i = 0; i < paths.size(); i++)
		totalActions += paths.at(i).steps.size();

	ConsoleHelper::PrintDebugInfo("[Entanglement Finder] Total search time:         " + to_string(ellapsed) + "ms", debugIndent);
	ConsoleHelper::PrintDebugInfo("[Entanglement Finder] Total Levels:              " + to_string(entanglementFinder->TotalLevels()), debugIndent);
	ConsoleHelper::PrintDebugInfo("[Entanglement Finder] Total Candidates:          " + to_string(entanglementEvaluator->RemovedCandidates() + candidates->size()), debugIndent);
	ConsoleHelper::PrintDebugInfo("[Entanglement Finder] Path Data:                 " + to_string(paths.size()) + " paths with " + to_string(totalActions) + " steps in total", debugIndent);
	ConsoleHelper::PrintDebugInfo("[Entanglement Evaluator] Total evaluation time:  " + to_string(ellapsed) + "ms", debugIndent);
	ConsoleHelper::PrintDebugInfo("[Entanglement Evaluator] Total Candidates:       " + to_string(candidates->size()) + " (" + to_string(entanglementEvaluator->RemovedCandidates()) + " removed)", debugIndent);
}

#pragma endregion
