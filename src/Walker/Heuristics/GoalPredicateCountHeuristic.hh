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
			int evalValue = Eval(&problem->goalState, &choices->at(i).action->effects, &choices->at(i).objects);
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

	int Eval(const PDDL::State* state, const std::vector<PDDL::Literal>* effects, const std::vector<unsigned int>* objects) const {
		int value = 0;

		for (auto effectLiteral = effects->begin(); effectLiteral != effects->end(); effectLiteral++) {
			if (effectLiteral->args.size() == 1) {
				if (state->ContainsFact(effectLiteral->predicateIndex, objects->at(effectLiteral->args.at(0))))
					value += 1;
			} else if (effectLiteral->args.size() == 2) {
				if (state->ContainsFact(effectLiteral->predicateIndex, std::make_pair(objects->at(effectLiteral->args.at(0)), objects->at(effectLiteral->args.at(1)))))
					value += 1;
			}
		}
		return value;
	};

	int Eval(const PDDL::State *state) const override {
		return 0;
	};
private:
	void Reset() override {};
};


#endif