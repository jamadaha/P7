#ifndef GOAL_PREDICATE_COUNT_HEURISTIC
#define GOAL_PREDICATE_COUNT_HEURISTIC

#include <unordered_set>
#include "BaseHeuristic.hh"

class GoalPredicateCountHeuristic : public BaseHeuristic {
public:
	GoalPredicateCountHeuristic(const PDDL::Domain *domain, const PDDL::Problem *problem) : BaseHeuristic(domain, problem){
		GenerateGoalPredicates();
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
	// The preconditions of actions which has an effect relating to goal state
	// e.g. goal: ball at some room - actions: drop - preconditions: holding ball & at-room 
	// Is a set as the case of same predicate different values is still valid
	std::unordered_set<unsigned int> goalPreconditions;

	void GenerateGoalPredicates() {
		std::unordered_set<const PDDL::Action*> actions = GetRelevantActions();
		for (auto action = actions.begin(); action != actions.end(); action++) {
			for (int i = 0; i < (*action)->preconditions.size(); i++) {
				const PDDL::Literal *literal = &(*action)->preconditions.at(i);
				goalPreconditions.emplace(literal->predicateIndex);
			}
		}
	}

	// Retries those PDDL::Action whose effect relates to the goal state
	// TODO: Handle cases where goal state requires something to be false
	std::unordered_set<const PDDL::Action*> GetRelevantActions() {
		std::unordered_set<const PDDL::Action*> actions;
		for (int i = 0; i < domain->actions.size(); i++) {
			const PDDL::Action *action = &domain->actions.at(i);
			for (int eff = 0; eff < action->effects.size(); eff++) {
				const PDDL::Literal *effect = &action->effects.at(eff);
				bool containsEffectFact = (problem->goalState.unaryFacts.contains(effect->predicateIndex) && problem->goalState.unaryFacts.at(effect->predicateIndex).size() > 0);
				if (effect->value && containsEffectFact)
					actions.emplace(action);
			}
		}
		return actions;
	}

	void Reset() override {};
};


#endif