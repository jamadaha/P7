#ifndef WALKER
#define WALKER

#include <vector>
#include <list>

#include "../IntermediatePDDL/PDDLActionInstance.hh"
#include "Heuristics/BaseHeuristic.hh"
#include "DepthFunctions/BaseDepthFunction.hh"
#include "WidthFunctions/BaseWidthFunction.hh"
#include "ActionGenerator.hpp"

#include "../Config/Config.hh"
#include "../Helpers/Hashes.hh"

#include "BaseWalker.hh"

class Walker : public BaseWalker {
public:
    Walker(PDDLInstance* instance, BaseHeuristic* heuristic, BaseDepthFunction* depthFunc, BaseWidthFunction* widthFunc) 
        : BaseWalker("Default", instance, heuristic, depthFunc, widthFunc) {}
    std::vector<Path> Walk() override;
private:
    Path Walk(BaseHeuristic* heuristic, BaseDepthFunction* depthFunction, const PDDLState* state);
};

#endif
