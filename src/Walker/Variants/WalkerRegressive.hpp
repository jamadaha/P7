#ifndef WALKER_REGRESSIVE
#define WALKER_REGRESSIVE

#include <vector>
#include <list>

#include "../../IntermediatePDDL/PDDLActionInstance.hh"
#include "../Heuristics/BaseHeuristic.hh"
#include "../DepthFunctions/BaseDepthFunction.hh"
#include "../WidthFunctions/BaseWidthFunction.hh"
#include "../ActionGenerator/ActionGeneratorRegressing.hpp"

#include "../../Config/Config.hh"
#include "../../Helpers/Hashes.hh"

#include "../BaseWalker.hh"

class WalkerRegressive : public BaseWalker {
public:
    WalkerRegressive(PDDLInstance* instance, BaseHeuristic* heuristic, BaseWidthFunction* widthFunc) 
        : BaseWalker("Default", instance, heuristic, widthFunc, new ActionGeneratorRegressing(instance)) {}
    std::vector<Path> Walk() override;
private:
    const unsigned int maxStepCount = 100;
    std::vector<Path> Walk(BaseHeuristic* heuristic, const PDDLState* state);

    PDDLState DoRegressiveAction(const PDDLState *state, const PDDLActionInstance *action);
};

#endif
