#include "RegressiveWalkerReformulator.hh"

std::vector<Path> RegressiveWalkerReformulator::PerformWalk(PDDLInstance* instance, bool debugMode) {
    auto walkerHeuistic = Configs->GetItem<std::string>("walkerHeuristic");
    auto walker = WalkerBuilder::BuildWalker("walkerRegressive", TimeLimit * (1 - Configs->GetItem<double>("reformulationTimeFraction")), walkerHeuistic, instance);
    if (debugMode)
        SetupWalkerDebugInfo(walker);
    return walker->Walk();
}
