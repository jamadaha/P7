#include "BaseWalkerReformulator.hh"

PDDLInstance BaseWalkerReformulator::ReformulatePDDL(PDDLInstance* instance) {
    bool debugMode = Configs->GetItem<bool>("debugmode");

    std::vector<Path> paths = PerformWalk(instance, debugMode);
    std::vector<EntanglementOccurance> candidates = FindEntanglements(instance, &paths, debugMode);
    this->macros = GenerateMacros(instance, &candidates, debugMode);
    PDDLInstance macroInstance = GenerateMacroInstance(instance, &macros, debugMode);

    return macroInstance;
}

std::vector<Path> BaseWalkerReformulator::PerformWalk(PDDLInstance *instance, bool debugMode) {
    int walkID = Report->Begin("Walking", ReportID);
	auto paths = PerformWalk(instance);
	auto ellapsed = Report->Stop(walkID);
	//if (debugMode)
		//PrintWalkerDebugData(ellapsed);
    return paths;
}

std::vector<EntanglementOccurance> BaseWalkerReformulator::FindEntanglements(PDDLInstance* instance, std::vector<Path>* paths, bool debugMode) {
    auto candidates = FindEntanglementCandidates(instance, paths, debugMode);
    return SanitizeCandidates(&candidates);
}

std::unordered_map<long unsigned int, EntanglementOccurance> BaseWalkerReformulator::FindEntanglementCandidates(PDDLInstance* instance, std::vector<Path>* paths, bool debugMode) {
	EntanglementFinder::RunData runData = EntanglementFinder::RunData();
	runData.LevelReductionFactor = Configs->GetItem<int>("levelReductionFactor");
	runData.SearchCeiling = Configs->GetItem<int>("searchCeiling");
	runData.SearchFloor = Configs->GetItem<int>("searchFloor");
	if (Configs->GetItem<std::string>("levelReductionTypes") == "Division")
		runData.LevelReductionType = EntanglementFinder::RunData::Division;
	if (Configs->GetItem<std::string>("levelReductionTypes") == "Subtraction")
		runData.LevelReductionType = EntanglementFinder::RunData::Subtraction;

	EntanglementFinder entanglementFinder = EntanglementFinder(runData);

	if (Configs->GetItem<bool>("debugmode")) {
		ProgressBarHelper* bar;
		entanglementFinder.OnNewLevel = [&](int level, int outOf) {
			bar = new ProgressBarHelper(outOf, "Finding Entanglements (level " + std::to_string(level) + ")", debugIndent + 1);
		};
		entanglementFinder.OnLevelIteration = [&](int current, int outOf) {
			bar->Update();
		};
		entanglementFinder.OnLevelEnd = [&]() {
			bar->End();
		};
	}

	return entanglementFinder.FindEntangledCandidates(paths);
}

std::vector<EntanglementOccurance> BaseWalkerReformulator::SanitizeCandidates(std::unordered_map<long unsigned int, EntanglementOccurance> *occurances) {
    EntanglementEvaluator::RunData runData;
	runData.MinimumQualityPercent = Configs->GetItem<double>("minimumQualityPercent");
	runData.MaxCandidates = Configs->GetItem<int>("maxCandidates");

	EntanglementEvaluator evaluator = EntanglementEvaluator(runData);
	if (Configs->GetItem<std::string>("entanglerLengthModifier") == "lengthBias")
		evaluator.LengthModifier = EntanglementEvaluatorModifiers::LengthModifiers::LengthBias;
	else if (Configs->GetItem<std::string>("entanglerLengthModifier") == "none")
		evaluator.LengthModifier = EntanglementEvaluatorModifiers::LengthModifiers::None;

	if (Configs->GetItem<std::string>("entanglerOccuranceModifier") == "none")
		evaluator.OccuranceModifier = EntanglementEvaluatorModifiers::OccuranceModifiers::None;
	if (Configs->GetItem<std::string>("entanglerOccuranceModifier") == "lowOccuranceBias")
		evaluator.OccuranceModifier = EntanglementEvaluatorModifiers::OccuranceModifiers::LowOccuranceBias;


	return evaluator.EvaluateAndSanitizeCandidates(*occurances);
}

std::vector<Macro> BaseWalkerReformulator::GenerateMacros(PDDLInstance* instance, std::vector<EntanglementOccurance>* candidates, bool debugMode) {
	if (debugMode)
		ConsoleHelper::PrintDebugInfo("[Macro Generator] Generating Macros...", debugIndent);
    std::vector<Macro> macros;
    for (auto iter = candidates->begin(); iter != candidates->end(); iter++)
        macros.push_back(MacroGenerator::GenerateMacro(&(*iter).Chain));
    return macros;
}

PDDLInstance BaseWalkerReformulator::GenerateMacroInstance(PDDLInstance* instance, std::vector<Macro> *macros, bool debugMode) {
    if (debugMode)
		ConsoleHelper::PrintDebugInfo("[Macro Generator] Generating Macro Instance...", debugIndent);
    return InstanceGenerator::GenerateInstance(instance->domain, instance->problem, macros);
}

SASPlan BaseWalkerReformulator::RebuildSASPlan(PDDLInstance *instance, SASPlan* reformulatedSAS) {
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