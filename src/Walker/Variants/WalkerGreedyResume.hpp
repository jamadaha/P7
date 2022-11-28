#ifndef WALKER_RESUMT
#define WALKER_RESUMT

#include <vector>
#include <list>

#include "../../PDDL/ActionInstance.hh"
#include "../Heuristics/BaseHeuristic.hh"
#include "../DepthFunctions/BaseDepthFunction.hh"
#include "../WidthFunctions/BaseWidthFunction.hh"
#include "../ActionGenerator.hpp"

#include "../../Config/Config.hh"
#include "../../Helpers/Hashes.hh"

#include "../BaseWalker.hh"

class WalkerGreedyResume : public BaseWalker {
public:
    WalkerGreedyResume(PDDL::Instance* instance, BaseHeuristic* heuristic, BaseWidthFunction* widthFunc)
        : BaseWalker("Default", instance, heuristic, widthFunc) {}
    std::vector<Path> Walk() override;
private:
    const unsigned int maxStepCount = 1000;
    int bestValue = 0;
    PDDL::State bestState;
    Path Walk(BaseHeuristic* heuristic, const PDDL::State state, unsigned int* current);
};

#endif
