#ifndef WALKER
#define WALKER

#include <vector>

#include "../IntermediatePDDL/PDDLActionInstance.hh"
#include "Heuristics/BaseHeuristics.hh"
#include "Heuristics/Contexts/PDDLContext.hh"
#include "DepthFunctions/BaseDepthFunction.hh"
#include "DepthFunctions/ObjectActionDepthFunction.hh"
#include "ActionGenerator.hpp"
#include "../RunReport/RunReport.hh"

struct Path {
    const std::vector<PDDLActionInstance> steps;
    const unsigned int actionCount;
    const unsigned int stepCount;
    Path(std::vector<PDDLActionInstance> steps, unsigned int actionCount, unsigned int stepCount) : steps(steps), actionCount(actionCount), stepCount(stepCount) {};
};

class Walker {
public:
    Walker(PDDLInstance* instance, ActionGenerator actionGenerator, BaseHeuristics<PDDLActionInstance, PDDLContext>* heuristic, BaseDepthFunction* depthFunc) : 
    instance(instance), actionGenerator(actionGenerator), heuristic(heuristic), depthFunc(depthFunc) {}
    Path Walk();
    Path Walk(PDDLState state);
private:
    PDDLInstance* instance;
    ActionGenerator actionGenerator;
    BaseHeuristics<PDDLActionInstance, PDDLContext>* heuristic;
    BaseDepthFunction* depthFunc;

    //PDDLState DoAction(PDDLState state, PDDLActionInstance action);
};

#endif
