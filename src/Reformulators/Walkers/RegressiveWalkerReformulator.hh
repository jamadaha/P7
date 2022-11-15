#ifndef REGRESSIVE_WALKER_REFORMULATOR
#define REGRESSIVE_WALKER_REFORMULATOR

#include "BaseWalkerReformulator.hh"
#include "../../Walker/WalkerBuilder.hpp"

class RegressiveWalkerReformulator : public BaseWalkerReformulator {
public:
    RegressiveWalkerReformulator(Config* config, RunReport* report) : BaseWalkerReformulator(config, report) {};

private:
    std::vector<Path> PerformWalk(PDDLInstance* instance, bool debugMode) override;
};

#endif