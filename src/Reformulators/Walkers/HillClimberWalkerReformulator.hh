#ifndef HILL_CLIMBER_WALKER_REFORMULATOR
#define HILL_CLIMBER_WALKER_REFORMULATOR

#include "BaseWalkerReformulator.hh"
#include "../../Walker/WalkerBuilder.hpp"

class HillClimberWalkerReformulator : public BaseWalkerReformulator {
public:
    HillClimberWalkerReformulator(Config *config, RunReport *report) : BaseWalkerReformulator(config, report) {} ;

private:
    std::vector<Path> PerformWalk(PDDL::Instance *instance, bool debugMode) override;
};

#endif