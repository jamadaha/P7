#ifndef SAS_PLAN_HH
#define SAS_PLAN_HH

#include <string>
#include <vector>

#include "SASAction"

namespace SAS {
    struct SASPlan {
        std::vector<SASAction> actions;
        int cost;
        int macrosUsed;

        SASPlan(std::vector<SASAction> actions, int cost, int macrosUsed) : actions(actions), cost(cost), macrosUsed(macrosUsed) {}
    };
}

#endif
