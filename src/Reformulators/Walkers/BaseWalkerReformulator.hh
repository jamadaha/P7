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
#include "../../EntanglementFinder/EntanglementFinder.hh"
#include "../../EntanglementFinder/EntanglementOccurance.hh"
#include "../../EntanglementFinder/EntanglementEvaluator.hh"
#include "../../EntanglementFinder/EntanglementEvaluatorModifiers.hh"
#include "../../MacroGenerator/MacroGenerator.hh"
#include "../../MacroGenerator/InstanceGenerator.hh"
#include "../../MacroVerifyer/MacroVerifyer.hh"
#include "../../SASRebuilder/SASRebuilder.hh"

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
    std::vector<EntanglementOccurance> FindEntanglements(PDDLInstance* instance, bool debugMode);
    EntanglementFinder GetEntanglementFinder(bool debugMode);
    EntanglementEvaluator GetEntanglementEvaluator();
    PDDLInstance GenerateMacros(PDDLInstance* instance, std::vector<EntanglementOccurance>* candidates, bool debugMode);

    void PrintEntanglerSteps(std::vector<EntanglementOccurance>* candidates, PDDLInstance* instance);
    void PrintWalkerDebugData(double ellapsed);
    void PrintEntanglerDebugData(double ellapsed, std::vector<EntanglementOccurance> *candidates, EntanglementFinder *entanglementFinder, EntanglementEvaluator *entanglementEvaluator);
};

#endif