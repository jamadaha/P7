#ifndef WALKER
#define WALKER

#include <vector>

#include "../PDDLTypes/PDDLActionInstance.hpp"
#include "Heuristics/BaseHeuristics.hh"
#include "Heuristics/Contexts/PDDLContext.h"
#include "DepthFunctions/BaseDepthFunction.h"

class Walker {
public:
    Walker(BaseHeuristics<PDDLActionInstance, PDDLContext>* heuristic, BaseDepthFunction* depthFunc) : heuristic(heuristic), depthFunc(depthFunc) {}
    void Walk();
private:
    BaseHeuristics<PDDLActionInstance, PDDLContext>* heuristic;
    BaseDepthFunction* depthFunc;
};

#endif
