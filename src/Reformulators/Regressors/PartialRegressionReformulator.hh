#ifndef PARTIAL_REGRESSION_REFORMULATOR
#define PARTIAL_REGRESSION_REFORMULATOR

#include "BaseRegressorReformulator.hh"

class PartialRegressionReformulator : public BaseRegressorReformulator {
public:
    PartialRegressionReformulator(Config *config, RunReport *report) : BaseRegressorReformulator(config, report) {};
protected:
    std::vector<Path> PerformRegression(PDDL::Instance *instance, bool debugMode) override;
};

#endif
