#ifndef WALKER_PROBE
#define WALKER_PROBE

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

class WalkerProbe : public BaseWalker {
public:
    WalkerProbe(PDDLInstance* instance, BaseHeuristic* heuristic, BaseWidthFunction* widthFunc)
        : BaseWalker("Default", instance, heuristic, widthFunc) {}
    std::vector<Path> Walk() override;
private:
    const unsigned int maxStepCount = 1000;
    std::unordered_set<Path> Walk(BaseHeuristic* heuristic, const PDDLState* state);
};

#endif
