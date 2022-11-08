#include "GreedyResumeWalkerReformulator.hh"

std::vector<Path> GreedyResumeWalkerReformulator::PerformWalk(PDDLInstance *instance, bool debugMode) {
    auto walkerHeuistic = Configs->GetItem<std::string>("walkerHeuristic");
    auto walker = WalkerBuilder::BuildWalker("walkerGreedyResume", TimeLimit, walkerHeuistic, instance);
        if (debugMode)
            SetupWalkerDebugInfo(walker);
    return walker->Walk();
}
