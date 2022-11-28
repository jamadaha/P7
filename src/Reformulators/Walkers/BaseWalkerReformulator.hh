#ifndef BASE_WALKER_REFORMULATOR
#define BASE_WALKER_REFORMULATOR

#include <vector>
#include <string>

#include "../BaseReformulator.hh"
#include "../../PDDL/Instance.hh"
#include "../../PDDL/ActionInstance.hh"
#include "../../Walker/Path.hh"
#include "../../Walker/BaseWalker.hh"

class BaseWalkerReformulator : public BaseReformulator {
public:
    BaseWalkerReformulator(Config *config, RunReport *report) : BaseReformulator(config, report) {};
	PDDL::Instance ReformulatePDDL(PDDL::Instance *instance) override;

protected:
    virtual std::vector<Path> PerformWalk(PDDL::Instance *instance, bool debugMode) = 0;
    void SetupWalkerDebugInfo(BaseWalker* walker);

private:
    ProgressBarHelper* walkerBar;

    void FindPaths(PDDL::Instance *instance, bool debugMode);

    void PrintWalkerDebugData(double ellapsed);
};

#endif