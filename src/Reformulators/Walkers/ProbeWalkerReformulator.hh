#ifndef PROBE_WALKER_REFORMULATOR
#define PROBE_WALKER_REFORMULATOR

#include "BaseWalkerReformulator.hh"
#include "../../Walker/WalkerBuilder.hpp"

class ProbeWalkerReformulator : public BaseWalkerReformulator {
public:
    ProbeWalkerReformulator(Config* config, RunReport* report) : BaseWalkerReformulator(config, report) {};

private:
    std::vector<Path> PerformWalk(PDDL::Instance* instance, bool debugMode) override;
};

#endif