#include "BaseRegressorReformulator.hh"

PDDLInstance BaseRegressorReformulator::ReformulatePDDL(PDDLInstance* instance) {
    bool debugMode = Configs->GetItem<bool>("debugmode");

	auto paths = PerformRegression(instance, debugMode);
    std::vector<EntanglementOccurance> candidates = FindEntanglements(instance, debugMode);
    GenerateMacros(instance, &candidates, debugMode);
    PDDLInstance macroInstance = GenerateMacroInstance(instance, &macros, debugMode);

    return macroInstance;

    return *instance;
}
