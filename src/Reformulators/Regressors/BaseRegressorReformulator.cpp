#include "BaseRegressorReformulator.hh"

PDDLInstance BaseRegressorReformulator::ReformulatePDDL(PDDLInstance* instance) {
    bool debugMode = Configs->GetItem<bool>("debugmode");

	// Walking
    FindPaths(instance, debugMode);

	// Entanglement Finding
    std::vector<EntanglementOccurance> candidates = FindEntanglements(instance, debugMode);

	// Macro Generation
	PDDLInstance macroInstance = GenerateMacros(instance, &candidates, debugMode);

    return macroInstance;
}

void BaseRegressorReformulator::FindPaths(PDDLInstance *instance, bool debugMode) {
    int regressID = Report->Begin("Walking", ReportID);	

    auto tempPaths = PerformRegression(instance, debugMode);
    for (int i = 0; i < tempPaths.size(); i++)
        this->paths.push_back(tempPaths.at(i));

    auto ellapsed = Report->Stop(regressID);

    ValidatePaths(instance, regressID, debugMode);
}
