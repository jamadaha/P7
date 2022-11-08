#ifndef BASE_WALKER_REFORMULATOR
#define BASE_WALKER_REFORMULATOR

#include <vector>
#include <string>

#include "../BaseReformulator.hh"
#include "../../Helpers/ProgressBarHelper.hh"
#include "../../IntermediatePDDL/PDDLInstance.hh"
#include "../../IntermediatePDDL/PDDLActionInstance.hh"
#include "../../Walker/Path.hpp"
#include "../../Walker/BaseWalker.hh"
#include "../../Walker/WalkerBuilder.hpp"
#include "../../EntanglementFinder/EntanglementFinder.hh"
#include "../../EntanglementFinder/EntanglementOccurance.hh"
#include "../../EntanglementFinder/EntanglementEvaluator.hh"
#include "../../EntanglementFinder/EntanglementEvaluatorModifiers.hh"
#include "../../MacroGenerator/MacroGenerator.hh"
#include "../../MacroGenerator/InstanceGenerator.hh"


class BaseWalkerReformulator : BaseReformulator {
public:
    BaseWalkerReformulator(Config *config, RunReport *report, BaseWalker *walker) : BaseReformulator(config, report), walker(walker) {

	}
	PDDLInstance ReformulatePDDL(PDDLInstance *instance) override;
    SASPlan RebuildSASPlan(PDDLInstance *instance, SASPlan* reformulatedSAS) override;
private:
    BaseWalker *walker = 0;
    std::vector<Macro> macros;
    ProgressBarHelper* walkerBar;

    std::vector<Path> FindPaths(PDDLInstance *instance, bool debugMode);
    std::vector<Path> PerformWalk(PDDLInstance *instance, bool debugMode);
    void SetupWalkerDebugInfo(BaseWalker* walker);
    std::vector<EntanglementOccurance> FindEntanglements(PDDLInstance* instance, std::vector<Path>* paths, bool debugMode);
    EntanglementFinder GetEntanglementFinder(bool debugMode);
    EntanglementEvaluator GetEntanglementEvaluator();
    std::vector<Macro> GenerateMacros(PDDLInstance* instance, std::vector<EntanglementOccurance>* candidates, bool debugMode);
    PDDLInstance GenerateMacroInstance(PDDLInstance* instance, std::vector<Macro> *macros, bool debugMode);

    void PrintEntanglerSteps(std::vector<EntanglementOccurance>* candidates, PDDLInstance* instance);
	void PrintWalkerDebugData(double ellapsed);
	void PrintEntanglerDebugData(double ellapsed, std::vector<EntanglementOccurance> *candidates, 
std::vector<Path> *paths, EntanglementFinder *entanglementFinder, EntanglementEvaluator *entanglementEvaluator);
};

#endif