#include "BaseWalkerReformulator.hh"

PDDLInstance BaseWalkerReformulator::ReformulatePDDL(PDDLInstance* instance) {
    bool debugMode = Configs->GetItem<bool>("debugmode");

    std::vector<Path> paths = PerformWalk(instance, debugMode);
    std::vector<EntanglementOccurance> candidates = FindEntanglements(instance, &paths, debugMode);
    std::vector<Macro> macros = GenerateMacros(instance, &candidates);
    PDDLInstance macroInstance = GenerateMacroInstance(instance, &macros);
}

SASPlan BaseWalkerReformulator::RebuildSASPlan(PDDLInstance *instance, SASPlan* reformulatedSAS) {

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

}

std::vector<EntanglementOccurance> BaseWalkerReformulator::FindEntanglements(PDDLInstance* instance, std::vector<Path>* paths) {
    
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

