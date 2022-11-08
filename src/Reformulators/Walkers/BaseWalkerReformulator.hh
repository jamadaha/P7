#ifndef BASE_WALKER_REFORMULATOR
#define BASE_WALKER_REFORMULATOR

#include <vector>
#include <string>

#include "../BaseReformulator.hh"
#include "../../Helpers/ProgressBarHelper.hh"
#include "../../IntermediatePDDL/PDDLInstance.hh"
#include "../../IntermediatePDDL/PDDLActionInstance.hh"
#include "../../Walker/Path.hpp"
#include "../../EntanglementFinder/EntanglementFinder.hh"
#include "../../EntanglementFinder/EntanglementOccurance.hh"
#include "../../EntanglementFinder/EntanglementEvaluator.hh"
#include "../../EntanglementFinder/EntanglementEvaluatorModifiers.hh"
#include "../../MacroGenerator/MacroGenerator.hh"
#include "../../MacroGenerator/InstanceGenerator.hh"


class BaseWalkerReformulator : BaseReformulator {
public:
    BaseWalkerReformulator(Config *config, RunReport *report) : BaseReformulator(config, report) {

	}
	PDDLInstance ReformulatePDDL(PDDLInstance *instance) override;
    SASPlan RebuildSASPlan(PDDLInstance *instance, SASPlan* reformulatedSAS) override;

protected:
    virtual std::vector<Path> PerformWalk(PDDLInstance *instance) = 0;

private:
    std::vector<Macro> macros;

    std::vector<Path> PerformWalk(PDDLInstance *instance, bool debugMode);
    std::vector<EntanglementOccurance> FindEntanglements(PDDLInstance* instance, std::vector<Path>* paths, bool debugMode);
    std::unordered_map<long unsigned int, EntanglementOccurance> FindEntanglementCandidates(PDDLInstance* instance, std::vector<Path>* paths, bool debugMode);
    std::vector<EntanglementOccurance> SanitizeCandidates(std::unordered_map<long unsigned int, EntanglementOccurance> *occurances);
    std::vector<Macro> GenerateMacros(PDDLInstance* instance, std::vector<EntanglementOccurance>* candidates, bool debugMode);
    PDDLInstance GenerateMacroInstance(PDDLInstance* instance, std::vector<Macro> *macros, bool debugMode);
};

#endif