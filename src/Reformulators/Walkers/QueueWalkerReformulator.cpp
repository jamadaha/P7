#include "QueueWalkerReformulator.hh"

std::vector<Path> QueueWalkerReformulator::PerformWalk(PDDL::Instance *instance, bool debugMode) {
    auto walkerHeuistic = Configs->GetItem<std::string>("walkerHeuristic");
    auto walker = WalkerBuilder::BuildWalker("walkerQueue", TimeLimit * (1 - Configs->GetItem<double>("reformulationTimeFraction")), walkerHeuistic, instance);
        if (debugMode)
            SetupWalkerDebugInfo(walker);
    walker->SaveStates = Configs->GetItem<bool>("validatePaths");
    auto paths = walker->Walk();
    actionsGenerated += walker->GetTotalActionsGenerated();
    actionIterationGenerated += walker->GetTotalIterations();
    auto factors = walker->GetBranchingFactors();
    copy(factors.begin(), factors.end(), back_inserter(branchingFactors));
    auto lengths = walker->GetPathLengths();
    copy(lengths.begin(), lengths.end(), back_inserter(pathLengths));
    return paths;
}
