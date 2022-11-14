#include "BaseReformulator.hh"

std::vector<EntanglementOccurance> BaseReformulator::FindEntanglements(PDDLInstance* instance, bool debugMode) {
    EntanglementFinder entanglementFinder = GetEntanglementFinder(debugMode);
    EntanglementEvaluator entanglementEvaluator = GetEntanglementEvaluator();
    int entangleID = Report->Begin("Finding Entanglements", ReportID);
    auto candidates = entanglementFinder.FindEntangledCandidates(&paths);
    auto sanitizedCandidates = entanglementEvaluator.EvaluateAndSanitizeCandidates(candidates);
	double ellapsed = Report->Stop();
	if (debugMode)
		PrintEntanglerDebugData(ellapsed, &sanitizedCandidates, &entanglementFinder, &entanglementEvaluator);
	if (Configs->GetItem<bool>("printentanglersteps"))
		PrintEntanglerSteps(&sanitizedCandidates, instance);
    return sanitizedCandidates;
}

EntanglementFinder BaseReformulator::GetEntanglementFinder(bool debugMode) {
    // Find entanglement candidates.
	auto runData = EntanglementFinder::RunData();

	runData.LevelReductionFactor = Configs->GetItem<int>("levelReductionFactor");
	runData.SearchCeiling = Configs->GetItem<int>("searchCeiling");
	runData.SearchFloor = Configs->GetItem<int>("searchFloor");
	if (Configs->GetItem<std::string>("levelReductionTypes") == "Division")
		runData.LevelReductionType = EntanglementFinder::RunData::Division;
	if (Configs->GetItem<std::string>("levelReductionTypes") == "Subtraction")
		runData.LevelReductionType = EntanglementFinder::RunData::Subtraction;

	auto ef = EntanglementFinder(runData);

	if (Configs->GetItem<bool>("debugmode")) {
		ProgressBarHelper* bar;
		ef.OnNewLevel = [&](int level, int outOf) {
			bar = new ProgressBarHelper(outOf, "Finding Entanglements (level " + std::to_string(level) + ")", debugIndent + 1);
		};
		ef.OnLevelIteration = [&](int current, int outOf) {
			bar->Update();
		};
		ef.OnLevelEnd = [&]() {
			bar->End();
		};
	}

	return ef;
}

EntanglementEvaluator BaseReformulator::GetEntanglementEvaluator() {
    EntanglementEvaluator::RunData runData;
	runData.MinimumQualityPercent = Configs->GetItem<double>("minimumQualityPercent");
	runData.MaxCandidates = Configs->GetItem<int>("maxCandidates");

	auto ee = EntanglementEvaluator(runData);
	if (Configs->GetItem<std::string>("entanglerLengthModifier") == "lengthBias")
		ee.LengthModifier = EntanglementEvaluatorModifiers::LengthModifiers::LengthBias;
	else if (Configs->GetItem<std::string>("entanglerLengthModifier") == "none")
		ee.LengthModifier = EntanglementEvaluatorModifiers::LengthModifiers::None;

	if (Configs->GetItem<std::string>("entanglerOccuranceModifier") == "none")
		ee.OccuranceModifier = EntanglementEvaluatorModifiers::OccuranceModifiers::None;
	else if (Configs->GetItem<std::string>("entanglerOccuranceModifier") == "lowOccuranceBias")
		ee.OccuranceModifier = EntanglementEvaluatorModifiers::OccuranceModifiers::LowOccuranceBias;

	return ee;
}

std::vector<Macro> BaseReformulator::GenerateMacros(PDDLInstance* instance, std::vector<EntanglementOccurance>* candidates, bool debugMode) {
	if (debugMode)
		ConsoleHelper::PrintDebugInfo("[Macro Generator] Generating Macros...", debugIndent);
    macros.clear();
	MacroGenerator macroGenerator = MacroGenerator(instance->domain);
    for (auto iter = candidates->begin(); iter != candidates->end(); iter++)
        macros.push_back(macroGenerator.GenerateMacro(&(*iter).Chain));
    return macros;
}

PDDLInstance BaseReformulator::GenerateMacroInstance(PDDLInstance* instance, std::vector<Macro> *macros, bool debugMode) {
    if (debugMode)
		ConsoleHelper::PrintDebugInfo("[Macro Generator] Generating Macro Instance...", debugIndent);
    return InstanceGenerator::GenerateInstance(instance->domain, instance->problem, macros);
}

SASPlan BaseReformulator::RebuildSASPlan(PDDLInstance *instance, SASPlan* reformulatedSAS) {
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


void BaseReformulator::PrintEntanglerSteps(std::vector<EntanglementOccurance>* candidates, PDDLInstance* instance) {
	ConsoleHelper::PrintDebugInfo("[Entanglement Evaluator] Top 10 Entanglements:", debugIndent);
	ConsoleHelper::PrintDebugInfo("[Entanglements] Quality  : Chain", debugIndent + 1);
	int counter = 0;
	for (auto i = candidates->begin(); i != candidates->end(); i++) {
		std::string actionStr = "";
		for (int j = 0; j < (*i).Chain.size(); j++) {
			auto item = (*i).Chain.at(j);
			std::string paramStr = "";
			for (int l = 0; l < item->objects.size(); l++) {
				paramStr += instance->problem->objects[item->objects[l]];
				if (l != item->objects.size() - 1)
					paramStr += ", ";
			}
			actionStr += item->action->name + "(" + paramStr + ")";
			if (j != (*i).Chain.size() - 1)
				actionStr += " -> ";
		}
		ConsoleHelper::PrintDebugInfo("[Entanglements] " + std::to_string((*i).Quality) + " : " + actionStr, debugIndent + 1);
		counter++;
		if (counter > 10)
			break;
	}
}

void BaseReformulator::PrintEntanglerDebugData(double ellapsed, std::vector<EntanglementOccurance> *candidates, EntanglementFinder *entanglementFinder, EntanglementEvaluator *entanglementEvaluator) {
	unsigned int totalActions = 0;
	for (int i = 0; i < paths.size(); i++)
		totalActions += paths.at(i).steps.size();

	ConsoleHelper::PrintDebugInfo("[Entanglement Finder] Total search time:         " + std::to_string(ellapsed) + "ms", debugIndent);
	ConsoleHelper::PrintDebugInfo("[Entanglement Finder] Total Levels:              " + std::to_string(entanglementFinder->TotalLevels()), debugIndent);
	ConsoleHelper::PrintDebugInfo("[Entanglement Finder] Total Candidates:          " + std::to_string(entanglementEvaluator->RemovedCandidates() + candidates->size()), debugIndent);
	ConsoleHelper::PrintDebugInfo("[Entanglement Finder] Path Data:                 " + std::to_string(paths.size()) + " paths with " + std::to_string(totalActions) + " steps in total", debugIndent);
	ConsoleHelper::PrintDebugInfo("[Entanglement Evaluator] Total evaluation time:  " + std::to_string(ellapsed) + "ms", debugIndent);
	ConsoleHelper::PrintDebugInfo("[Entanglement Evaluator] Total Candidates:       " + std::to_string(candidates->size()) + " (" + std::to_string(entanglementEvaluator->RemovedCandidates()) + " removed)", debugIndent);
}
