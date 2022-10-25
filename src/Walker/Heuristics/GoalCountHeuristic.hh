#ifndef GOAL_COUNT_HEURISTIC
#define GOAL_COUNT_HEURISTIC

#include "BaseHeuristic.hh"

class GoalCountHeuristic : public BaseHeuristic {
public:
	GoalCountHeuristic(const PDDLDomain *domain, const PDDLProblem *problem) : BaseHeuristic(domain, problem){};

	PDDLActionInstance* NextChoice(const PDDLState * state, std::vector<PDDLActionInstance> *choices) const override {
		printf("FIX!\n");
		return &choices->at(rand() % choices->size());
	}

	int Eval(const PDDLState *state) const override {
		return rand();
	};
};

#endif