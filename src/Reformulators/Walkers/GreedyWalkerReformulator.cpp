#include "GreedyWalkerReformulator.hh"

std::vector<Path> GreedyWalkerReformulator::PerformWalk(PDDLInstance *instance, bool debugMode) {
    auto walkerHeuistic = Configs->GetItem<std::string>("walkerHeuristic");
    auto walker = WalkerBuilder::BuildWalker("walkerGreedy", TimeLimit, walkerHeuistic, instance);
        if (debugMode)
            SetupWalkerDebugInfo(walker);
    return walker->Walk();
}
