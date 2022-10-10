#ifndef WALKER
#define WALKER

#include <vector>

#include "../PDDLTypes/PDDLActionInstance.hpp"
#include "Heuristics/BaseHeuristics.hh"
#include "Heuristics/Contexts/PDDLContext.h"
#include "DepthFunctions/BaseDepthFunction.h"
#include "ActionGenerator.hpp"

class Walker {
public:
    Walker(PDDLInstance* instance, ActionGenerator actionGenerator, BaseHeuristics<PDDLActionInstance, PDDLContext>* heuristic, BaseDepthFunction* depthFunc) : instance(instance), actionGenerator(actionGenerator), heuristic(heuristic), depthFunc(depthFunc) {}
    void Walk();
private:
    PDDLInstance* instance;
    ActionGenerator actionGenerator;
    BaseHeuristics<PDDLActionInstance, PDDLContext>* heuristic;
    BaseDepthFunction* depthFunc;
};

#endif
