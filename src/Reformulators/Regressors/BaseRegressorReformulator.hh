#ifndef BASE_REGRESSOR_REFORMULATOR
#define BASE_REGRESSOR_REFORMULATOR

#include <vector>
#include <string>

#include "../BaseReformulator.hh"

class BaseRegressorReformulator : public BaseReformulator {
public:
    BaseRegressorReformulator(Config *config, RunReport *report) : BaseReformulator(config, report) {};
	PDDLInstance ReformulatePDDL(PDDLInstance *instance) override;
    SASPlan RebuildSASPlan(PDDLInstance *instance, SASPlan* reformulatedSAS) override;

protected:

private:
};

#endif