#include "WalkerBuilder.hpp"

BaseWalker* WalkerBuilder::BuildWalker(std::string walkerName, unsigned int width, std::string heuristicName, PDDL::Instance *instance) {
    BaseWidthFunction *widthFunction = GetWidthFunction(width);
    BaseHeuristic *heuristic = GetHeuristic(heuristicName, instance);
    return GetWalker(walkerName, widthFunction, heuristic, instance);
}

BaseWidthFunction* WalkerBuilder::GetWidthFunction(unsigned int width) {
    return new TimeWidthFunction(width);
}

BaseHeuristic* WalkerBuilder::GetHeuristic(std::string heuristicName, PDDL::Instance *instance) {
    if (heuristicName == "random")
		return new RandomHeuristic();
	else if (heuristicName == "goalCount")
		return new GoalCountHeuristic(instance->domain, instance->problem);
	else if (heuristicName == "goalPredicateCount")
		return new GoalPredicateCountHeuristic(instance->domain, instance->problem);
	else if (heuristicName == "previousBaseHeuristic")
		return new PreviousBaseHeuristic(instance->domain, instance->problem);
	else
		throw std::invalid_argument("Invalid heuristic specified in config");
}

BaseWalker* WalkerBuilder::GetWalker(std::string walkerName, BaseWidthFunction *widthFunction, BaseHeuristic *heuristic, PDDL::Instance *instance) {
    if (walkerName == "walkerGreedy")
		return new WalkerGreedy(instance, heuristic, widthFunction);
	else if (walkerName == "walkerGreedyResume")
		return new WalkerGreedyResume(instance, heuristic, widthFunction);
	else if (walkerName == "walkerQueue")
		return new WalkerQueue(instance, heuristic, widthFunction);
	else if (walkerName == "walkerProbe")
		return new WalkerProbe(instance, heuristic, widthFunction);
	else if (walkerName == "walkerStepBack")
		return new WalkerStepBack(instance, heuristic, widthFunction);
	else
		throw std::invalid_argument("Invalid walker specified in config");
}
