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
			int evalValue = Eval(nullptr, &choices->at(i));
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
		int value = 0;

		if (state != nullptr) {
			for (auto goalUnaryFacts = problem->goalState.unaryFacts.begin(); goalUnaryFacts != problem->goalState.unaryFacts.end(); goalUnaryFacts++) {
				for (auto fact = goalUnaryFacts->second.begin(); fact != goalUnaryFacts->second.end(); fact++) {
					if (state->ContainsFact(goalUnaryFacts->first, *fact))
						value += 1;
				}
			}
			for (auto goalBinaryFacts = problem->goalState.binaryFacts.begin(); goalBinaryFacts != problem->goalState.binaryFacts.end(); goalBinaryFacts++) {
				for (auto fact = goalBinaryFacts->second.begin(); fact != goalBinaryFacts->second.end(); fact++) {
					if (state->ContainsFact(goalBinaryFacts->first, *fact))
						value += 1;
				}
			}
		}

		if (action != nullptr) {
			for (auto effectLiteral = action->action->effects.begin(); effectLiteral != action->action->effects.end(); effectLiteral++) {
				if (effectLiteral->args.size() == 1) {
					if (problem->goalState.ContainsFact(effectLiteral->predicateIndex, action->objects.at(effectLiteral->args.at(0))))
						if (effectLiteral->value)
							value += 1;
				}
				else if (effectLiteral->args.size() == 2) {
					if (problem->goalState.ContainsFact(effectLiteral->predicateIndex, std::make_pair(action->objects.at(effectLiteral->args.at(0)), action->objects.at(effectLiteral->args.at(1)))))
						if (effectLiteral->value)
							value += 1;
				}
			}
		}
		return value;
	};

private:
	void Reset() override {};
};


#endif