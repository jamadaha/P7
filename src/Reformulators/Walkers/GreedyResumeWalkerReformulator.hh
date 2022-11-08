#ifndef GREEDY_RESUME_WALKER_REFORMULATOR
#define GREEDY_RESUME_WALKER_REFORMULATOR

#include "BaseWalkerReformulator.hh"
#include "../../Walker/WalkerBuilder.hpp"

class GreedyResumeWalkerReformulator : public BaseWalkerReformulator {
public:
    GreedyResumeWalkerReformulator(Config *config, RunReport *report) : BaseWalkerReformulator(config, report) {} ;

private:
    std::vector<Path> PerformWalk(PDDLInstance *instance, bool debugMode) override;
};

#endif