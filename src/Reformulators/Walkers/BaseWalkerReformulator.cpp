#include "BaseWalkerReformulator.hh"

PDDL::Instance BaseWalkerReformulator::ReformulatePDDL(PDDL::Instance* instance) {
    bool debugMode = Configs->GetItem<bool>("debugmode");

	// Walking
    FindPaths(instance, debugMode);

	// Entanglement Finding
    std::vector<JointPaths::JointPath> candidates = FindEntanglements(instance, debugMode);

	// Macro Generation
	PDDL::Instance macroInstance = GenerateMacros(instance, &candidates, debugMode);

    return macroInstance;
}

void BaseWalkerReformulator::FindPaths(PDDL::Instance *instance, bool debugMode) {
    int walkID = Report->Begin("Walking", ReportID);
	auto tempPaths = PerformWalk(instance, debugMode);
	for (auto iter = tempPaths.begin(); iter != tempPaths.end(); iter++)
		paths.push_back((*iter));
	auto ellapsed = Report->Stop(walkID);
	if (debugMode)
		PrintWalkerDebugData(ellapsed);
	ValidatePaths(instance, walkID, debugMode);
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
		walker->OnTempStateMade = [&](PDDL::Instance* instance, PDDL::State* state) {
			std::string command = "echo '" + state->ToString(instance) + "'" + " >> walkerLog";
			system(command.c_str());

		};
		walker->OnStateWalk = [&](PDDL::Instance* instance, PDDL::State* state, PDDL::ActionInstance* chosenAction) {
			std::string stateinfo = state->ToString(instance);
			std::string actioninfo = chosenAction->ToString(instance);
			std::string content = "echo '" + actioninfo + "\n" + stateinfo + "'" + " >> walkerLog";

			system(content.c_str());
        };
    }
}

void BaseWalkerReformulator::PrintWalkerDebugData(double ellapsed) {
	ConsoleHelper::PrintDebugInfo("[Walker] Total walk time:         " + std::to_string(ellapsed) + "ms", debugIndent);
}

#pragma endregion
