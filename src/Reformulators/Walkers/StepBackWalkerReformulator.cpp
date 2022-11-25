#include "StepBackWalkerReformulator.hh"

std::vector<Path> StepBackWalkerReformulator::PerformWalk(PDDLInstance* instance, bool debugMode) {
    auto walkerHeuistic = Configs->GetItem<std::string>("walkerHeuristic");
    auto walker = WalkerBuilder::BuildWalker("walkerStepBack", TimeLimit * (1 - Configs->GetItem<double>("reformulationTimeFraction")), walkerHeuistic, instance);
    if (debugMode)
        SetupWalkerDebugInfo(walker);
    walker->SaveStates = Configs->GetItem<bool>("validatePaths");
    return walker->Walk();
}