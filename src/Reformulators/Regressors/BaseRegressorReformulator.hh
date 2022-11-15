#ifndef BASE_REGRESSOR_REFORMULATOR
#define BASE_REGRESSOR_REFORMULATOR

#include <vector>
#include <string>

#include "../BaseReformulator.hh"

class BaseRegressorReformulator : public BaseReformulator {
public:
    BaseRegressorReformulator(Config *config, RunReport *report) : BaseReformulator(config, report) {};
	PDDLInstance ReformulatePDDL(PDDLInstance *instance) override;

protected:
    virtual std::vector<Path> PerformRegression(PDDLInstance *instance, bool debugMode) = 0;

private:
    void FindPaths(PDDLInstance *instance, bool debugMode);
};

#endif