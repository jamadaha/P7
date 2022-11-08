#ifndef QUEUE_WALKER_REFORMULATOR
#define QUEUE_WALKER_REFORMULATOR

#include "BaseWalkerReformulator.hh"
#include "../../Walker/WalkerBuilder.hpp"

class QueueWalkerReformulator : public BaseWalkerReformulator {
public:
    QueueWalkerReformulator(Config *config, RunReport *report) : BaseWalkerReformulator(config, report) {} ;

private:
    std::vector<Path> PerformWalk(PDDLInstance *instance, bool debugMode) override;
};

#endif