#ifndef SAS_PLAN_HH
#define SAS_PLAN_HH

#include <string>
#include <vector>

#include "Action.hh"

namespace SAS {
    struct Plan {
        std::vector<Action> actions;
        int cost;
        int macrosUsed;

        Plan(std::vector<Action> actions, int cost, int macrosUsed) : actions(actions), cost(cost), macrosUsed(macrosUsed) {}
    };
}

#endif
