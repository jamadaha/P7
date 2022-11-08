#ifndef GREEDY_WALKER_REFORMULATOR
#define GREEDY_WALKER_REFORMULATOR

#include "BaseWalkerReformulator.hh"
#include "../../Walker/WalkerBuilder.hpp"

class GreedyWalkerReformulator : public BaseWalkerReformulator {
public:
    GreedyWalkerReformulator(Config *config, RunReport *report) : BaseWalkerReformulator(config, report) {} ;

private:
    ProgressBarHelper* walkerBar;

    std::vector<Path> PerformWalk(PDDLInstance *instance, bool debugMode) override;

    void SetupWalkerDebugInfo(BaseWalker* walker);
};

#endif