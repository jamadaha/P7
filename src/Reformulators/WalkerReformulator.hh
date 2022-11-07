#ifndef WalkerReformulator_HH
#define WalkerReformulator_HH

#include <chrono>
#include <unordered_map>
#include <unordered_set>

#include "BaseReformulator.hh"
#include "../Walker/BaseWalker.hh"
#include "../Walker/WalkerBuilder.hpp"
#include "../Config/Config.hh"
#include "../Helpers/ConsoleHelper.hh"
#include "../EntanglementFinder/EntanglementFinder.hh"
#include "../EntanglementFinder/EntanglementOccurance.hh"
#include "../EntanglementFinder/EntanglementEvaluator.hh"
#include "../EntanglementFinder/EntanglementEvaluatorModifiers.hh"
#include "../Helpers/ProgressBarHelper.hh"
#include "../MacroGenerator/MacroGenerator.hh"
#include "../MacroGenerator/InstanceGenerator.hh"

class WalkerReformulator : public BaseReformulator {
public:
	WalkerReformulator(Config* config, RunReport* report) : BaseReformulator(config, report) {

	}
	PDDLInstance ReformulatePDDL(PDDLInstance* instance) override;
	SASPlan RebuildSASPlan(PDDLInstance *instance, SASPlan* reformulatedSAS) override;
private:
	std::vector<Path> PerformWalk(PDDLInstance* instance);
	std::vector<EntanglementOccurance> FindEntanglements(std::vector<Path>* paths, PDDLInstance* instance);
	PDDLInstance GenerateMacros(std::vector<EntanglementOccurance>* candidates, PDDLInstance* instance);
	
	EntanglementFinder* entanglementFinder;
	EntanglementEvaluator* entanglementEvaluator;
	MacroGenerator* macroGenerator;
	std::vector<Path> paths;
	std::vector<Macro> macros;
	ProgressBarHelper* walkerBar;

	void PrintEntanglerSteps(std::vector<EntanglementOccurance>* candidates, PDDLInstance* instance);
	void PrintWalkerDebugData(double ellapsed);
	void PrintEntanglerDebugData(double ellapsed, std::vector<EntanglementOccurance>* candidates);
	void SetupWalkerDebugInfo(BaseWalker* walker);
};

#endif