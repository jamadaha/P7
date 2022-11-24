#include "BaseWalkerReformulator.hh"

PDDLInstance BaseWalkerReformulator::ReformulatePDDL(PDDLInstance* instance) {
    bool debugMode = Configs->GetItem<bool>("debugmode");

	// Walking
    FindPaths(instance, debugMode);

	// Entanglement Finding
    std::vector<JointPaths::JointPath> candidates = FindEntanglements(instance, debugMode);

	// Macro Generation
	PDDLInstance macroInstance = GenerateMacros(instance, &candidates, debugMode);

    return macroInstance;
}

void BaseWalkerReformulator::FindPaths(PDDLInstance *instance, bool debugMode) {
    int walkID = Report->Begin("Walking", ReportID);
	auto tempPaths = PerformWalk(instance, debugMode);
	for (auto iter = tempPaths.begin(); iter != tempPaths.end(); iter++)
		paths.push_back((*iter));
	auto ellapsed = Report->Stop(walkID);
	if (debugMode)
		PrintWalkerDebugData(ellapsed);
	if (Configs->GetItem<bool>("validatePaths")) {
		int verifyID = Report->Begin("Verifying Paths", walkID);
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

std::vector<JointPaths::JointPath> BaseWalkerReformulator::FindEntanglements(PDDLInstance* instance, bool debugMode) {
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

JointPaths::Finder BaseWalkerReformulator::GetEntanglementFinder(bool debugMode) {
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

	auto ef = JointPaths::Finder(runData);

	if (Configs->GetItem<bool>("debugmode")) {
		ef.OnNewLevel = [&](int level, int outOf) {
			entanglerBar = new ProgressBarHelper(outOf, "Finding Entanglements (level " + std::to_string(level) + ")", debugIndent + 1);
		};
		ef.OnLevelIteration = [&](int current, int outOf) {
			entanglerBar->Update();
		};
		ef.OnLevelEnd = [&]() {
			entanglerBar->End();
			delete entanglerBar;
		};
		ef.OnTimeLimitReached = [&]() {
			if (entanglerBar != nullptr) {
				entanglerBar->End();
				delete entanglerBar;
			}
			ConsoleHelper::PrintDebugWarning("[Entanglement Finder] Time limit reached!", debugIndent);
		};
	}

	return ef;
}

JointPaths::Evaluator BaseWalkerReformulator::GetEntanglementEvaluator() {
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

PDDLInstance BaseWalkerReformulator::GenerateMacros(PDDLInstance* instance, std::vector<JointPaths::JointPath>* candidates, bool debugMode) {
	if (debugMode)
		ConsoleHelper::PrintDebugInfo("[Macro Generator] Generating Macros...", debugIndent);

	int macroGenerateID = Report->Begin("Generating Macros", ReportID);
	macros.clear();
	MacroGenerator macroGenerator = MacroGenerator(instance->domain);
    for (auto iter = candidates->begin(); iter != candidates->end(); iter++)
        macros.push_back(macroGenerator.GenerateMacro(&(*iter).Chain));
	macrosGenerated = macros.size();

	if (Configs->GetItem<bool>("verifyMacros"))
	{
		Report->Begin("Verifying Macros", macroGenerateID);
		if (debugMode)
			ConsoleHelper::PrintDebugInfo("[Macro Generator] Verifying Macros...", debugIndent);
		MacroVerifyer verifyer;
		auto badMacros = verifyer.VerifyMacros(&macros, instance->domain);
		if (badMacros.size() == 0)
			Report->Stop(ReportData("None","-1", "true"));
		else
			Report->Stop(ReportData("None", "-1", "false"));

		int counter = 0;
		for (auto macro : badMacros) {
			ConsoleHelper::PrintError("[Macro Generator] Bad macro: " + macro.macro.name + ", Reason: " + macro.Reason, debugIndent);
			encounteredErrors = true;
			counter++;
			if (counter > 10) {
				ConsoleHelper::PrintError("[Macro Generator] Many more than these", debugIndent);
				break;
			}
		}
	}

	if (debugMode)
		ConsoleHelper::PrintDebugInfo("[Macro Generator] Generating Macro Instance...", debugIndent);
	auto result = InstanceGenerator::GenerateInstance(instance->domain, instance->problem, &macros);
	Report->Stop(macroGenerateID);
	return result;
}

SASPlan BaseWalkerReformulator::RebuildSASPlan(PDDLInstance *instance, SASPlan* reformulatedSAS) {
    std::vector<SASAction> actions;
	int macrosUsed = 0;
	for (int i = 0; i < reformulatedSAS->actions.size(); i++) {
		auto sasAction = reformulatedSAS->actions.at(i);
		if (sasAction.name.starts_with("macro")) {
			for (auto macro : macros) {
				auto tempActionName = StringHelper::ToUpper(sasAction.name);
				auto tempMacroName = StringHelper::ToUpper(macro.name);
				if (tempActionName == tempMacroName) {
					macrosUsed++;
					for (auto macroAction : macro.path) {
						std::vector<std::string> args; args.reserve(macroAction.objects.size());
						for (auto object : macroAction.objects)
							args.push_back(instance->problem->objects.at(object));
						actions.push_back(SASAction(macroAction.action->name, args));
					}
					break;
				}
			}
		}
		else {
			actions.push_back(sasAction);
		}
	}
	// Do Something and give a "corrected" SAS plan back
	SASPlan newPlan = SASPlan(actions, actions.size(), macrosUsed);
	return newPlan;
}

#pragma region Debug Items

void BaseWalkerReformulator::SetupWalkerDebugInfo(BaseWalker* walker) {
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
		delete walkerBar;
		unsigned int totalIterations = sender->GetTotalIterations();
		unsigned int totalActionCount = sender->GetTotalActionsGenerated();
		ConsoleHelper::PrintDebugInfo("[Walker] Total walk time:         " + std::to_string(timePassed) + "ms", debugIndent);
		double iterationsPrSecond = (totalIterations * 1000) / (timePassed + 1);
		ConsoleHelper::PrintDebugInfo("[Walker] Total walker iterations: " + std::to_string(totalIterations) + " [" + std::to_string(iterationsPrSecond) + "/s]", debugIndent);
		double actionsPrSecond = (totalActionCount * 1000) / (timePassed + 1);
		ConsoleHelper::PrintDebugInfo("[Walker] Total actions Generated: " + std::to_string(totalActionCount) + " [" + std::to_string(actionsPrSecond) + "/s]", debugIndent);
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

void BaseWalkerReformulator::PrintEntanglerSteps(std::vector<JointPaths::JointPath>* candidates, PDDLInstance* instance) {
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

void BaseWalkerReformulator::PrintWalkerDebugData(double ellapsed) {
	ConsoleHelper::PrintDebugInfo("[Walker] Total walk time:         " + std::to_string(ellapsed) + "ms", debugIndent);
}

void BaseWalkerReformulator::PrintEntanglerDebugData(double ellapsed, std::vector<JointPaths::JointPath> *candidates, JointPaths::Finder* finder, JointPaths::Evaluator* evaluator) {
	unsigned int totalActions = 0;
	for (int i = 0; i < paths.size(); i++)
		totalActions += paths.at(i).steps.size();

	ConsoleHelper::PrintDebugInfo("[Entanglement Finder] Total search time:         " + std::to_string(ellapsed) + "ms", debugIndent);
	ConsoleHelper::PrintDebugInfo("[Entanglement Finder] Total Levels:              " + std::to_string(finder->TotalLevels()), debugIndent);
	ConsoleHelper::PrintDebugInfo("[Entanglement Finder] Total Candidates:          " + std::to_string(evaluator->RemovedCandidates() + candidates->size()), debugIndent);
	ConsoleHelper::PrintDebugInfo("[Entanglement Finder] Path Data:                 " + std::to_string(paths.size()) + " paths with " + std::to_string(totalActions) + " steps in total", debugIndent);
	ConsoleHelper::PrintDebugInfo("[Entanglement Evaluator] Total Candidates:       " + std::to_string(candidates->size()) + " (" + std::to_string(evaluator->RemovedCandidates()) + " removed)", debugIndent);
}

#pragma endregion
