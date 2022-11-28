#include "StepBackWalkerReformulator.hh"

std::vector<Path> StepBackWalkerReformulator::PerformWalk(PDDL::Instance* instance, bool debugMode) {
    auto walkerHeuistic = Configs->GetItem<std::string>("walkerHeuristic");
    auto walker = WalkerBuilder::BuildWalker("walkerStepBack", TimeLimit * (1 - Configs->GetItem<double>("reformulationTimeFraction")), walkerHeuistic, instance);
    if (debugMode)
        SetupWalkerDebugInfo(walker);
    walker->SaveStates = Configs->GetItem<bool>("validatePaths");
    auto paths = walker->Walk();
    actionsGenerated += walker->GetTotalActionsGenerated();
    actionIterationGenerated += walker->GetTotalIterations();
    branchingFactors = walker->GetBranchingFactors();
    return paths;
}
