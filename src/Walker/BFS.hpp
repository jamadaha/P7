#ifndef B_F_S
#define B_F_S

#include <vector>
#include <list>
#include <queue>

#include "../IntermediatePDDL/PDDLActionInstance.hh"
#include "Heuristics/BaseHeuristic.hh"
#include "DepthFunctions/BaseDepthFunction.hh"
#include "WidthFunctions/BaseWidthFunction.hh"
#include "ActionGenerator.hpp"

#include "../Config/Config.hh"
#include "../Helpers/Hashes.hh"

#include "BaseWalker.hh"

class BFS : public BaseWalker {
public:
    BFS(PDDLInstance* instance, BaseHeuristic* heuristic, BaseWidthFunction* widthFunc) 
        : BaseWalker("Default", instance, heuristic, widthFunc) {}
    std::vector<Path> Walk() override;
private:
    Path Walk(BaseHeuristic* heuristic, const PDDLState* state);
};

#endif
