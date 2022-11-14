#include "BaseWalkerReformulator.hh"

PDDLInstance BaseWalkerReformulator::ReformulatePDDL(PDDLInstance* instance) {
    bool debugMode = Configs->GetItem<bool>("debugmode");

    FindPaths(instance, debugMode);
    std::vector<EntanglementOccurance> candidates = FindEntanglements(instance, debugMode);
    GenerateMacros(instance, &candidates, debugMode);
    PDDLInstance macroInstance = GenerateMacroInstance(instance, &macros, debugMode);

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

void BaseWalkerReformulator::PrintWalkerDebugData(double ellapsed) {
	ConsoleHelper::PrintDebugInfo("[Walker] Total walk time:         " + std::to_string(ellapsed) + "ms", debugIndent);
}

#pragma endregion
