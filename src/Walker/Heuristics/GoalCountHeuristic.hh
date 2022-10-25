#ifndef GOAL_COUNT_HEURISTIC
#define GOAL_COUNT_HEURISTIC

#include "BaseHeuristics.hh"

class GoalCountHeuristic : public BaseHeuristics {
public:
	GoalCountHeuristic(const PDDLDomain *domain, const PDDLProblem *problem) : BaseHeuristics(domain, problem){};

	int Eval(const PDDLState *state) const override {
		return rand();
	};
};

#endif