#ifndef SAS_PLAN_HH
#define SAS_PLAN_HH

#include <string>
#include <vector>

#include "Action.hh"

namespace SAS {
    struct Plan {
        const std::vector<Action> actions;
        const int cost;
        const int macrosUsed;
        const int uniqueMacrosUsed;

        Plan(std::vector<Action> actions, int cost, int macrosUsed, int uniqueMacrosUsed) : actions(actions), cost(cost), macrosUsed(macrosUsed), uniqueMacrosUsed(uniqueMacrosUsed) {}
    };
}

#endif
