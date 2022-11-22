#include "QueueWalkerReformulator.hh"

std::vector<Path> QueueWalkerReformulator::PerformWalk(PDDLInstance *instance, bool debugMode) {
    auto walkerHeuistic = Configs->GetItem<std::string>("walkerHeuristic");
    auto walker = WalkerBuilder::BuildWalker("walkerQueue", TimeLimit * (1 - Configs->GetItem<double>("reformulationTimeFraction")), walkerHeuistic, instance);
        if (debugMode)
            SetupWalkerDebugInfo(walker);
        walker->SaveStates = Configs->GetItem<bool>("validatePaths");
    return walker->Walk();
}
