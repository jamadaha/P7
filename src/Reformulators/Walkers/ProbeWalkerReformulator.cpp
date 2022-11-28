#include "ProbeWalkerReformulator.hh"

std::vector<Path> ProbeWalkerReformulator::PerformWalk(PDDL::Instance* instance, bool debugMode) {
    auto walkerHeuistic = Configs->GetItem<std::string>("walkerHeuristic");
    auto walker = WalkerBuilder::BuildWalker("walkerProbe", TimeLimit * (1 - Configs->GetItem<double>("reformulationTimeFraction")), walkerHeuistic, instance);
    if (debugMode)
        SetupWalkerDebugInfo(walker);
    walker->SaveStates = Configs->GetItem<bool>("validatePaths");
    return walker->Walk();
}
