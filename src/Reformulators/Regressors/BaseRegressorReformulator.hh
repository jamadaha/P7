#ifndef BASE_REGRESSOR_REFORMULATOR
#define BASE_REGRESSOR_REFORMULATOR

#include <vector>
#include <string>
#include <filesystem>

#include "../BaseReformulator.hh"
#include "../DownwardRunner/H2Runner.hh"
#include "../DownwardRunner/DownwardRunner.hh"

class BaseRegressorReformulator : public BaseReformulator {
public:
    BaseRegressorReformulator(Config *config, RunReport *report) : BaseReformulator(config, report) {};
	PDDL::Instance ReformulatePDDL(PDDL::Instance *instance) override;

protected:
    virtual std::vector<Path> PerformRegression(PDDL::Instance *instance, bool debugMode) = 0;

private:
    void FindPaths(PDDL::Instance *instance, bool debugMode);
    void GetMutexes(PDDL::Instance* instance, bool debugMode);
    bool HaveRunPreprocessor = false;
};

#endif