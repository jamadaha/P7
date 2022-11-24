#ifndef BASE_WALKER_REFORMULATOR
#define BASE_WALKER_REFORMULATOR

#include <vector>
#include <string>

#include "../BaseReformulator.hh"
#include "../../Helpers/ProgressBarHelper.hh"
#include "../../IntermediatePDDL/PDDLInstance.hh"
#include "../../IntermediatePDDL/PDDLActionInstance.hh"
#include "../../Walker/Path.hh"
#include "../../Walker/BaseWalker.hh"
#include "../../WalkerPathVerifyer/WalkerPathVerifyer.hh"
#include "../../JointPaths/Evaluator/Evaluator.hh"
#include "../../JointPaths/Evaluator/EvaluationModifiers.hh"
#include "../../JointPaths/Finder/Finder.hh"
#include "../../JointPaths/JointPath.hh"
#include "../../MacroGenerator/MacroGenerator.hh"
#include "../../MacroGenerator/InstanceGenerator.hh"
#include "../../MacroVerifyer/MacroVerifyer.hh"

class BaseWalkerReformulator : public BaseReformulator {
public:
    BaseWalkerReformulator(Config *config, RunReport *report) : BaseReformulator(config, report) {};
	PDDLInstance ReformulatePDDL(PDDLInstance *instance) override;
    SASPlan RebuildSASPlan(PDDLInstance *instance, SASPlan* reformulatedSAS) override;

protected:
    virtual std::vector<Path> PerformWalk(PDDLInstance *instance, bool debugMode) = 0;
    void SetupWalkerDebugInfo(BaseWalker* walker);

private:
    std::vector<Path> paths;
    std::vector<Macro> macros;
    ProgressBarHelper* walkerBar;
    ProgressBarHelper* entanglerBar;

    void FindPaths(PDDLInstance *instance, bool debugMode);
    std::vector<JointPaths::JointPath> FindEntanglements(PDDLInstance* instance, bool debugMode);
    JointPaths::Finder GetEntanglementFinder(bool debugMode);
    JointPaths::Evaluator GetEntanglementEvaluator();
    PDDLInstance GenerateMacros(PDDLInstance* instance, std::vector<JointPaths::JointPath>* candidates, bool debugMode);

    void PrintEntanglerSteps(std::vector<JointPaths::JointPath>* candidates, PDDLInstance* instance);
    void PrintWalkerDebugData(double ellapsed);
    void PrintEntanglerDebugData(double ellapsed, std::vector<JointPaths::JointPath> *candidates, JointPaths::Finder *entanglementFinder, JointPaths::Evaluator *entanglementEvaluator);
};

#endif