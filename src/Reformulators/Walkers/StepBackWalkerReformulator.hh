#ifndef STEP_BACK_WALKER_REFORMULATOR
#define STEP_BACK_WALKER_REFORMULATOR

#include "BaseWalkerReformulator.hh"
#include "../../Walker/WalkerBuilder.hpp"

class StepBackWalkerReformulator : public BaseWalkerReformulator {
public:
    StepBackWalkerReformulator(Config* config, RunReport* report) : BaseWalkerReformulator(config, report) {};

private:
    std::vector<Path> PerformWalk(PDDLInstance* instance, bool debugMode) override;
};

#endif