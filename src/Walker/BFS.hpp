#ifndef B_F_S
#define B_F_S

#include <vector>
#include <list>
#include <queue>

#include "../IntermediatePDDL/PDDLActionInstance.hh"
#include "Heuristics/BaseHeuristic.hh"
#include "DepthFunctions/BaseDepthFunction.hh"
#include "DepthFunctions/ObjectActionDepthFunction.hh"
#include "WidthFunctions/BaseWidthFunction.hh"
#include "ActionGenerator.hpp"

#include "../Config/Config.hh"
#include "../Helpers/Hashes.hh"

#include "BaseWalker.hh"

class BFS : public BaseWalker {
public:
    BFS(PDDLInstance* instance, ActionGenerator actionGenerator, BaseHeuristic* heuristic, BaseDepthFunction* depthFunc, BaseWidthFunction* widthFunc) 
        : BaseWalker("Default", instance, actionGenerator, heuristic, depthFunc, widthFunc) {}
    std::vector<Path> Walk() override;
private:
    Path Walk(BaseHeuristic* heuristic, BaseDepthFunction* depthFunction, const PDDLState* state);
};

#endif
