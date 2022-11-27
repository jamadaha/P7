#ifndef WALKER_BUILDER
#define WALKER_BUILDER

#include "BaseWalker.hh"
#include "Variants/WalkerGreedy.hpp"
#include "Variants/WalkerGreedyResume.hpp"
#include "Variants/WalkerQueue.hpp"
#include "Variants/WalkerProbe.hpp"
#include "Variants/WalkerStepBack.hpp"

#include "DepthFunctions/BaseDepthFunction.hh"
#include "DepthFunctions/ConstantDepthFunction.hh"

#include "WidthFunctions/BaseWidthFunction.hh"
#include "WidthFunctions/ConstantWidthFunction.hh"
#include "WidthFunctions/TimeWidthFunction.hh"

#include "Heuristics/BaseHeuristic.hh"
#include "Heuristics/GoalCountHeuristic.hh"
#include "Heuristics/GoalPredicateCountHeuristic.hh"
#include "Heuristics/RandomHeuristic.hh"
#include "Heuristics/PreviousBaseHeuristic.hh"

#include "../PDDL/Instance.hh"

class WalkerBuilder {
public:
    static BaseWalker* BuildWalker(std::string walkerName, unsigned int width, std::string heuristicName, PDDL::Instance *instance);
private:

    static BaseDepthFunction* GetDepthFunction();
    static BaseWidthFunction* GetWidthFunction(unsigned int width);
	static BaseHeuristic* GetHeuristic(std::string heuristicName, PDDL::Instance *instance);
	static BaseWalker* GetWalker(std::string walkerName, BaseWidthFunction *widthFunction, BaseHeuristic *heuristic, PDDL::Instance *instance);
};

#endif
