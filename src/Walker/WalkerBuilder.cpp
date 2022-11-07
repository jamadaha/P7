#include "WalkerBuilder.hpp"

BaseWalker* WalkerBuilder::BuildWalker(std::string walkerName, unsigned int width, std::string heuristicName, PDDLInstance *instance) {
    BaseWidthFunction *widthFunction = GetWidthFunction(width);
    BaseHeuristic *heuristic = GetHeuristic(heuristicName, instance);
    return GetWalker(walkerName, widthFunction, heuristic);
}

BaseWidthFunction* WalkerBuilder::GetWidthFunction(unsigned int width) {
    return new ConstantWidthFunction(width);
}

BaseHeuristic* WalkerBuilder::GetHeuristic(std::string heuristicName, PDDLInstance *instance) {
    if (heuristicName == "random")
		return new RandomHeuristic();
	else if (heuristicName == "goalCount")
		return new GoalCountHeuristic(instance->domain, instance->problem);
	else if (heuristicName == "goalPredicateCount")
		return new GoalPredicateCountHeuristic(instance->domain, instance->problem);
	else
		throw std::invalid_argument("Invalid heuristic specified in config");
}

BaseWalker* WalkerBuilder::GetWalker(std::string walkerName, BaseWidthFunction *widthFunction, BaseHeuristic *heuristic) {
    
}
