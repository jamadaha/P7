#ifndef WALKER_RESUMT
#define WALKER_RESUMT

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

class WalkerResume : public BaseWalker {
public:
    WalkerResume(PDDLInstance* instance, BaseHeuristic* heuristic, BaseWidthFunction* widthFunc) 
        : BaseWalker("Default", instance, heuristic, widthFunc) {}
    std::vector<Path> Walk() override;
private:
    const unsigned int maxStepCount = 1000;
    int bestValue = 0;
    PDDLState bestState;
    Path Walk(BaseHeuristic* heuristic, const PDDLState* state);
};

#endif
