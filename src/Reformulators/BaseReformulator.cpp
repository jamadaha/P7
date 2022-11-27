#include "BaseReformulator.hh"

void BaseReformulator::ValidatePaths(PDDLInstance *instance, int parentReportID, bool debugMode) {
	if (Configs->GetItem<bool>("validatePaths")) {
		int verifyID = Report->Begin("Verifying Paths", parentReportID);
		if (debugMode) {
			ConsoleHelper::PrintDebugInfo("[Walker] Verifying paths", debugIndent);
			ConsoleHelper::PrintDebugWarning("[Walker] This may take a while", debugIndent);
		}

		WalkerPathVerifyer verifyer;
		auto badPaths = verifyer.VerifyPaths(&paths, instance, Configs);
		if (badPaths.size() == 0) {
			if (debugMode)
				ConsoleHelper::PrintDebugInfo("[Walker] " + std::to_string(paths.size()) + " paths verified!", debugIndent);
			Report->Stop(ReportData("None", "-1", "true"));
		}
		else {
			Report->Stop(ReportData("None", "-1", "false"));
			int counter = 0;
			for (auto path : badPaths) {
				ConsoleHelper::PrintError("[Walker] Bad path: " + path.path.ToString(instance->problem) + ", Reason: " + path.Reason, debugIndent);
				encounteredErrors = true;
				counter++;
				if (counter > 10) {
					ConsoleHelper::PrintError("[Walker] Many more than these", debugIndent);
					break;
				}
			}
		}
	}
}

std::vector<JointPaths::JointPath> BaseReformulator::FindEntanglements(PDDLInstance* instance, bool debugMode) {
    JointPaths::Finder finder = GetEntanglementFinder(debugMode);
    JointPaths::Evaluator evaluator = GetEntanglementEvaluator();
    int entangleID = Report->Begin("Finding Entanglements", ReportID);
    auto candidates = finder.FindEntangledCandidates(&paths);
    auto sanitizedCandidates = evaluator.EvaluateAndSanitizeCandidates(candidates);
	double ellapsed = Report->Stop();
	if (debugMode)
		PrintEntanglerDebugData(ellapsed, &sanitizedCandidates, &finder, &evaluator);
	if (Configs->GetItem<bool>("printentanglersteps"))
		PrintEntanglerSteps(&sanitizedCandidates, instance);
    return sanitizedCandidates;
}

JointPaths::Finder BaseReformulator::GetEntanglementFinder(bool debugMode) {
	// Find entanglement candidates.
	auto runData = JointPaths::Finder::RunData();

	runData.LevelReductionFactor = Configs->GetItem<int>("levelReductionFactor");
	runData.SearchCeiling = Configs->GetItem<int>("searchCeiling");
	runData.SearchFloor = Configs->GetItem<int>("searchFloor");
	runData.TimeLimitMs = TimeLimit * Configs->GetItem<double>("reformulationTimeFraction");
	if (Configs->GetItem<std::string>("levelReductionTypes") == "Division")
		runData.LevelReductionType = JointPaths::Finder::RunData::Division;
	if (Configs->GetItem<std::string>("levelReductionTypes") == "Subtraction")
		runData.LevelReductionType = JointPaths::Finder::RunData::Subtraction;

	auto finder = JointPaths::Finder(runData);

	if (Configs->GetItem<bool>("debugmode")) {
		finder.OnNewLevel = [&](int level, int outOf) {
			entanglerBar = new ProgressBarHelper(outOf, "Finding Entanglements (level " + std::to_string(level) + ")", debugIndent + 1);
		};
		finder.OnLevelIteration = [&](int current, int outOf) {
			entanglerBar->Update();
		};
		finder.OnLevelEnd = [&]() {
			entanglerBar->End();
			delete entanglerBar;
		};
		finder.OnTimeLimitReached = [&]() {
			if (entanglerBar != nullptr) {
				entanglerBar->End();
				delete entanglerBar;
			}
			ConsoleHelper::PrintDebugWarning("[Entanglement Finder] Time limit reached!", debugIndent);
		};
	}

	return finder;
}

JointPaths::Evaluator BaseReformulator::GetEntanglementEvaluator() {
	JointPaths::Evaluator::RunData runData;
	runData.MinimumQualityPercent = Configs->GetItem<double>("minimumQualityPercent");
	runData.MaxCandidates = Configs->GetItem<int>("maxCandidates");

	auto ee = JointPaths::Evaluator(runData);
	if (Configs->GetItem<std::string>("entanglerLengthModifier") == "lengthBias")
		ee.LengthModifier = JointPaths::EvaluationModifiers::LengthModifiers::LengthBias;
	else if (Configs->GetItem<std::string>("entanglerLengthModifier") == "none")
		ee.LengthModifier = JointPaths::EvaluationModifiers::LengthModifiers::None;

	if (Configs->GetItem<std::string>("entanglerOccuranceModifier") == "none")
		ee.OccuranceModifier = JointPaths::EvaluationModifiers::OccuranceModifiers::None;
	else if (Configs->GetItem<std::string>("entanglerOccuranceModifier") == "lowOccuranceBias")
		ee.OccuranceModifier = JointPaths::EvaluationModifiers::OccuranceModifiers::LowOccuranceBias;

	return ee;
}

PDDLInstance BaseReformulator::GenerateMacros(PDDLInstance* instance, std::vector<JointPaths::JointPath>* candidates, bool debugMode) {
	if (debugMode)
		ConsoleHelper::PrintDebugInfo("[Macro Generator] Generating Macros...", debugIndent);

	int macroGenerateID = Report->Begin("Generating Macros", ReportID);
	macros.clear();
	MacroGenerator macroGenerator = MacroGenerator(instance->domain);
	for (auto iter = candidates->begin(); iter != candidates->end(); iter++)
		macros.push_back(macroGenerator.GenerateMacro(&(*iter).Chain));
	macrosGenerated = macros.size();

	if (debugMode)
		ConsoleHelper::PrintDebugInfo("[Macro Generator] Generating Macro Instance...", debugIndent);
	auto result = InstanceGenerator::GenerateInstance(instance->domain, instance->problem, &macros);
	Report->Stop(macroGenerateID);
	return result;
}

SAS::Plan BaseReformulator::RebuildSASPlan(PDDLInstance *instance, SAS::Plan* reformulatedSAS) {
	SAS::Rebuilder builder = SAS::Rebuilder(instance, &macros);
	return builder.RebuildSASPlan(reformulatedSAS);
}

void BaseReformulator::PrintEntanglerSteps(std::vector<JointPaths::JointPath>* candidates, PDDLInstance* instance) {
	ConsoleHelper::PrintDebugInfo("[Entanglement Evaluator] Top 10 Entanglements:", debugIndent);
	ConsoleHelper::PrintDebugInfo("[Entanglements] Quality  : Chain", debugIndent + 1);
	int counter = 0;
	for (auto i = candidates->begin(); i != candidates->end(); i++) {
		std::string actionStr = "";
		for (int j = 0; j < (*i).Chain.size(); j++) {
			auto item = (*i).Chain.at(j);
			std::string paramStr = "";
			for (int l = 0; l < item.objects.size(); l++) {
				paramStr += instance->problem->objects[item.objects[l]];
				if (l != item.objects.size() - 1)
					paramStr += ", ";
			}
			actionStr += item.action->name + "(" + paramStr + ")";
			if (j != (*i).Chain.size() - 1)
				actionStr += " -> ";
		}
		ConsoleHelper::PrintDebugInfo("[Entanglements] " + std::to_string((*i).Quality) + " : " + actionStr, debugIndent + 1);
		counter++;
		if (counter > 10)
			break;
	}
}

void BaseReformulator::PrintEntanglerDebugData(double ellapsed, std::vector<JointPaths::JointPath> *candidates, JointPaths::Finder *entanglementFinder, JointPaths::Evaluator *entanglementEvaluator) {
	unsigned int totalActions = 0;
	for (int i = 0; i < paths.size(); i++)
		totalActions += paths.at(i).steps.size();

	ConsoleHelper::PrintDebugInfo("[Entanglement Finder] Total search time:         " + std::to_string(ellapsed) + "ms", debugIndent);
	ConsoleHelper::PrintDebugInfo("[Entanglement Finder] Total Levels:              " + std::to_string(entanglementFinder->TotalLevels()), debugIndent);
	ConsoleHelper::PrintDebugInfo("[Entanglement Finder] Total Candidates:          " + std::to_string(entanglementEvaluator->RemovedCandidates() + candidates->size()), debugIndent);
	ConsoleHelper::PrintDebugInfo("[Entanglement Finder] Path Data:                 " + std::to_string(paths.size()) + " paths with " + std::to_string(totalActions) + " steps in total", debugIndent);
	ConsoleHelper::PrintDebugInfo("[Entanglement Evaluator] Total Candidates:       " + std::to_string(candidates->size()) + " (" + std::to_string(entanglementEvaluator->RemovedCandidates()) + " removed)", debugIndent);
}
