#ifndef WALKER_BUILDER
#define WALKER_BUILDER

#include "BaseWalker.hh"
#include "Variants/Walker.hpp"
#include "Variants/WalkerResume.hpp"

#include "DepthFunctions/BaseDepthFunction.hh"
#include "DepthFunctions/ConstantDepthFunction.hh"

#include "WidthFunctions/BaseWidthFunction.hh"
#include "WidthFunctions/ConstantWidthFunction.hh"
#include "WidthFunctions/TimeWidthFunction.hh"

#include "Heuristics/BaseHeuristic.hh"
#include "Heuristics/GoalCountHeuristic.hh"
#include "Heuristics/GoalPredicateCountHeuristic.hh"
#include "Heuristics/RandomHeuristic.hh"
#include "Heuristics/GreedyHeuristic.hh"

#include "../IntermediatePDDL/PDDLInstance.hh"

class WalkerBuilder {
public:
    static BaseWalker* BuildWalker(std::string walkerName, unsigned int width, std::string heuristicName, PDDLInstance *instance);
private:

    static BaseDepthFunction* GetDepthFunction();
    static BaseWidthFunction* GetWidthFunction(unsigned int width);
	static BaseHeuristic* GetHeuristic(std::string heuristicName, PDDLInstance *instance);
	static BaseWalker* GetWalker(std::string walkerName, BaseWidthFunction *widthFunction, BaseHeuristic *heuristic, PDDLInstance *instance);
};

#endif
