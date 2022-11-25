#ifndef BASE_WALKER_REFORMULATOR
#define BASE_WALKER_REFORMULATOR

#include <vector>
#include <string>

#include "../BaseReformulator.hh"
#include "../../IntermediatePDDL/PDDLInstance.hh"
#include "../../IntermediatePDDL/PDDLActionInstance.hh"
#include "../../Walker/Path.hh"
#include "../../Walker/BaseWalker.hh"

class BaseWalkerReformulator : public BaseReformulator {
public:
    BaseWalkerReformulator(Config *config, RunReport *report) : BaseReformulator(config, report) {};
	PDDLInstance ReformulatePDDL(PDDLInstance *instance) override;

protected:
    virtual std::vector<Path> PerformWalk(PDDLInstance *instance, bool debugMode) = 0;
    void SetupWalkerDebugInfo(BaseWalker* walker);

private:
    ProgressBarHelper* walkerBar;

    void FindPaths(PDDLInstance *instance, bool debugMode);

    void PrintWalkerDebugData(double ellapsed);
};

#endif