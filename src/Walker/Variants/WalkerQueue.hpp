#ifndef WALKER_QUEUE
#define WALKER_QUEUE

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

class WalkerQueue : public BaseWalker {
public:
    WalkerQueue(PDDL::Instance* instance, BaseHeuristic* heuristic, BaseWidthFunction* widthFunc)
        : BaseWalker("Default", instance, heuristic, widthFunc) {}
    std::vector<Path> Walk() override;
private:
    const unsigned int maxStepCount = 100;
    static constexpr auto cmp = [](std::pair<int, std::pair<PDDL::State, Path>> a, std::pair<int, std::pair<PDDL::State, Path>> b) { return a.first > b.first; };
    std::multiset<std::pair<int, std::pair<PDDL::State, Path>>, decltype(cmp)> searchQueue;
    Path Walk(BaseHeuristic* heuristic, const PDDL::State state);
};

#endif
