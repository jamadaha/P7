#include "WalkerBuilder.hpp"

BaseWalker* WalkerBuilder::BuildWalker(std::string walkerName, unsigned int width, std::string heuristicName, PDDLInstance *instance, ActionGenerator* actionGenerator) {
    BaseWidthFunction *widthFunction = GetWidthFunction(width);
    BaseHeuristic *heuristic = GetHeuristic(heuristicName, instance);
    return GetWalker(walkerName, widthFunction, heuristic, instance, actionGenerator);
}

BaseWidthFunction* WalkerBuilder::GetWidthFunction(unsigned int width) {
    return new TimeWidthFunction(width);
}

BaseHeuristic* WalkerBuilder::GetHeuristic(std::string heuristicName, PDDLInstance *instance) {
    if (heuristicName == "random")
		return new RandomHeuristic();
	else if (heuristicName == "goalCount")
		return new GoalCountHeuristic(instance->domain, instance->problem);
	else if (heuristicName == "goalPredicateCount")
		return new GoalPredicateCountHeuristic(instance->domain, instance->problem);
	else if (heuristicName == "greedyHeuristic")
		return new GreedyHeuristic(instance->domain, instance->problem);
	else
		throw std::invalid_argument("Invalid heuristic specified in config");
}

BaseWalker* WalkerBuilder::GetWalker(std::string walkerName, BaseWidthFunction *widthFunction, BaseHeuristic *heuristic, PDDLInstance *instance, ActionGenerator* actionGenerator) {
    if (walkerName == "walker")
		return new Walker(instance, heuristic, widthFunction, actionGenerator);
	else
		throw std::invalid_argument("Invalid walker specified in config");
}
