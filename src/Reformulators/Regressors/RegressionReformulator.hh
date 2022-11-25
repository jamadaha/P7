#ifndef REGRESSION_REFORMULATOR
#define REGRESSION_REFORMULATOR

#include "BaseRegressorReformulator.hh"

class RegressionReformulator : public BaseRegressorReformulator {
public:
    RegressionReformulator(Config *config, RunReport *report) : BaseRegressorReformulator(config, report) {};
protected:
    std::vector<Path> PerformRegression(PDDLInstance *instance, bool debugMode) override;   
};

#endif
