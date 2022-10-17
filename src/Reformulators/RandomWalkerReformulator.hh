#ifndef RandomWalkerReformulator_HH
#define RandomWalkerReformulator_HH

#include "BaseReformulator.hh"
#include "../Walker/Walker.hpp"
#include "../Walker/Heuristics/RandomHeuristic.hh"
#include "../Walker/DepthFunctions/ConstantDepthFunction.hh"
#include "../Walker/WidthFunctions/TimeWidthFunction.hh"
#include "../Config/config.hh"

class RandomWalkerReformulator : public BaseReformulator {
public:
	RandomWalkerReformulator(Config* config) : BaseReformulator(config) {

	}
	PDDLInstance ReformulatePDDL(PDDLInstance* instance) override;
	SASPlan RebuildSASPlan(SASPlan* reformulatedSAS) override;
};

#endif