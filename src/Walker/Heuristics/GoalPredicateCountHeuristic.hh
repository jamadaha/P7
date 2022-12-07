#ifndef GOAL_PREDICATE_COUNT_HEURISTIC
#define GOAL_PREDICATE_COUNT_HEURISTIC

#include <unordered_set>
#include "BaseHeuristic.hh"

class GoalPredicateCountHeuristic : public BaseHeuristic {
public:
	GoalPredicateCountHeuristic(const PDDL::Domain *domain, const PDDL::Problem *problem) : BaseHeuristic(domain, problem){
	};

	PDDL::ActionInstance* NextChoice(PDDL::State * state, std::vector<PDDL::ActionInstance> *choices) override {
		int bestIndex = -1;
		int bestValue = -1;
		for (int i = 0; i < choices->size(); i++) {
			int evalValue = Eval(&problem->goalState, &choices->at(i));
			if (evalValue > bestValue) {
				bestValue = evalValue;
				bestIndex = i;
			}
		}
		if (bestValue == 0)
			return &choices->at(rand() % choices->size());
		else
			return &choices->at(bestIndex);
	}

	int Eval(const PDDL::State* state, const PDDL::ActionInstance* action) const override {
		if (action == nullptr)
			return 0;

		int value = 0;

		for (auto effectLiteral = action->action->effects.begin(); effectLiteral != action->action->effects.end(); effectLiteral++) {
			if (effectLiteral->args.size() == 1) {
				if (state->ContainsFact(effectLiteral->predicateIndex, action->objects.at(effectLiteral->args.at(0))))
					value += 1;
			} else if (effectLiteral->args.size() == 2) {
				if (state->ContainsFact(effectLiteral->predicateIndex, std::make_pair(action->objects.at(effectLiteral->args.at(0)), action->objects.at(effectLiteral->args.at(1)))))
					value += 1;
			}
		}
		return value;
	};

private:
	void Reset() override {};
};


#endif