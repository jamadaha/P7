#ifndef RandomWalkerReformulator_HH
#define RandomWalkerReformulator_HH

#include <chrono>

#include "BaseReformulator.hh"
#include "../Walker/Walker.hpp"
#include "../Walker/Heuristics/RandomHeuristic.hh"
#include "../Walker/DepthFunctions/ConstantDepthFunction.hh"
#include "../Walker/WidthFunctions/ConstantWidthFunction.hh"
#include "../Walker/WidthFunctions/TimeWidthFunction.hh"
#include "../Config/Config.hh"
#include "../Helpers/ConsoleHelper.hh"
#include "../EntanglementFinder/EntanglementFinder.hh"

class RandomWalkerReformulator : public BaseReformulator {
public:
	RandomWalkerReformulator(Config* config) : BaseReformulator(config) {

	}
	PDDLInstance ReformulatePDDL(PDDLInstance* instance) override;
	SASPlan RebuildSASPlan(SASPlan* reformulatedSAS) override;
private:
	std::vector<Path> PerformWalk(PDDLInstance* instance);
	std::vector<EntangledActionsSet> FindEntanglements(PDDLInstance* instance, std::vector<Path> paths);
	PDDLInstance GenerateMacros(std::vector<EntangledActionsSet> candidates, PDDLInstance* instance);
};

#endif