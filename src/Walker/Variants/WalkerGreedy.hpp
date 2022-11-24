#ifndef WALKER_GREEDY
#define WALKER_GREEDY

#include <vector>
#include <list>

#include "../../IntermediatePDDL/PDDLActionInstance.hh"
#include "../Heuristics/BaseHeuristic.hh"
#include "../DepthFunctions/BaseDepthFunction.hh"
#include "../WidthFunctions/BaseWidthFunction.hh"
#include "../ActionGenerator.hpp"

#include "../../Config/Config.hh"
#include "../../Helpers/Hashes.hh"

#include "../BaseWalker.hh"

class WalkerGreedy : public BaseWalker {
public:
    WalkerGreedy(PDDLInstance* instance, BaseHeuristic* heuristic, BaseWidthFunction* widthFunc) 
        : BaseWalker("Default", instance, heuristic, widthFunc) {}
    std::vector<Path> Walk() override;
private:
    const unsigned int maxStepCount = 1000;
    Path Walk(BaseHeuristic* heuristic, const PDDLState* state, unsigned int* current);
};

#endif
