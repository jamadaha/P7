#include "ProbeWalkerReformulator.hh"

std::vector<Path> ProbeWalkerReformulator::PerformWalk(PDDLInstance* instance, bool debugMode) {
    auto walkerHeuistic = Configs->GetItem<std::string>("walkerHeuristic");
    auto walker = WalkerBuilder::BuildWalker("walkerProbe", TimeLimit, walkerHeuistic, instance);
    if (debugMode)
        SetupWalkerDebugInfo(walker);
    return walker->Walk();
}
