#ifndef WALKER_QUEUE
#define WALKER_QUEUE

#include <vector>
#include <list>

#include "../../IntermediatePDDL/PDDLActionInstance.hh"
#include "../Heuristics/BaseHeuristic.hh"
#include "../DepthFunctions/BaseDepthFunction.hh"
#include "../WidthFunctions/BaseWidthFunction.hh"
#include "../ActionGenerator/ActionGenerator.hpp"

#include "../../Config/Config.hh"
#include "../../Helpers/Hashes.hh"

#include "../BaseWalker.hh"

class WalkerQueue : public BaseWalker {
public:
    WalkerQueue(PDDLInstance* instance, BaseHeuristic* heuristic, BaseWidthFunction* widthFunc) 
        : BaseWalker("Default", instance, heuristic, widthFunc) {}
    std::vector<Path> Walk() override;
private:
    const unsigned int maxStepCount = 1000;
    static constexpr auto cmp = [](std::pair<int, std::pair<PDDLState, Path>> a, std::pair<int, std::pair<PDDLState, Path>> b) { return a.first > b.first; };
    std::multiset<std::pair<int, std::pair<PDDLState, Path>>, decltype(cmp)> searchQueue;
    std::unordered_set<Path> Walk(BaseHeuristic* heuristic, const PDDLState* state);
};

#endif
