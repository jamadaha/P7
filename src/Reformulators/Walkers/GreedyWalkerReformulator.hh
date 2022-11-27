#ifndef GREEDY_WALKER_REFORMULATOR
#define GREEDY_WALKER_REFORMULATOR

#include "BaseWalkerReformulator.hh"
#include "../../Walker/WalkerBuilder.hpp"

class GreedyWalkerReformulator : public BaseWalkerReformulator {
public:
    GreedyWalkerReformulator(Config *config, RunReport *report) : BaseWalkerReformulator(config, report) {} ;

private:
    std::vector<Path> PerformWalk(PDDL::Instance *instance, bool debugMode) override;
};

#endif