#ifndef WalkerReformulator_HH
#define WalkerReformulator_HH

#include <chrono>
#include <unordered_map>
#include <unordered_set>

#include "BaseReformulator.hh"
#include "../Walker/Walker.hpp"
#include "../Walker/Heuristics/RandomHeuristic.hh"
#include "../Walker/Heuristics/GoalCountHeuristic.hh"
#include "../Walker/Heuristics/GoalPredicateCountHeuristic.hh"
#include "../Walker/DepthFunctions/ConstantDepthFunction.hh"
#include "../Walker/WidthFunctions/ConstantWidthFunction.hh"
#include "../Walker/WidthFunctions/TimeWidthFunction.hh"
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
	WalkerReformulator(Config* config, RunReport *report, int timeLimit) : BaseReformulator(config, report, timeLimit) {

	}
	PDDLInstance ReformulatePDDL(PDDLInstance* instance) override;
	SASPlan RebuildSASPlan(PDDLInstance *instance, SASPlan* reformulatedSAS) override;
private:
	std::vector<Macro> macros;
	std::vector<Path> PerformWalk(PDDLInstance* instance);
	std::vector<EntanglementOccurance> FindEntanglements(std::vector<Path>* paths, PDDLInstance* instance);
	PDDLInstance GenerateMacros(std::vector<EntanglementOccurance> candidates, PDDLInstance* instance);
};

#endif