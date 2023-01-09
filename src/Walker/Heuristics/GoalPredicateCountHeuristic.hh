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
			auto changes = state->DoAction(&choices->at(i));
			int evalValue = Eval(state);
			state->UndoAction(&changes);
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

	int Eval(const PDDL::State* state) const override {
		int value = 0;
		for (auto iter = problem->goalState.unaryFacts.begin(); iter != problem->goalState.unaryFacts.end(); iter++)
			for (auto factIter = (*iter).second.begin(); factIter != (*iter).second.end(); factIter++)
				if (state->ContainsFact((*iter).first, &(*factIter)))
					value += 1000;
		for (auto iter = problem->goalState.binaryFacts.begin(); iter != problem->goalState.binaryFacts.end(); iter++)
			for (auto factIter = (*iter).second.begin(); factIter != (*iter).second.end(); factIter++)
				if (state->ContainsFact((*iter).first, (*factIter)))
					value += 1000;
		for (auto iter = goalPreconditions.begin(); iter != goalPreconditions.end(); iter++) {
			if (domain->predicates.at((*iter)).arguments.size() == 1)
				value += state->unaryFacts.at((*iter)).size();
			else
				value += state->binaryFacts.at((*iter)).size();
		}
		
		return value;
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
			const auto action = domain->actions.at(i);
			for (int eff = 0; eff < action.effects.size(); eff++) {
                const auto effect = action.effects.at(eff);
				const auto effectPredicate = effect.predicateIndex;
				if (!effect.value)
                    continue;

                if (problem->goalState.unaryFacts.contains(effectPredicate)) {
                    if (!problem->goalState.unaryFacts.at(effectPredicate).empty())
                        actions.emplace(&domain->actions.at(i));
                } else if (problem->goalState.binaryFacts.contains(effectPredicate)) {
                    if (!problem->goalState.binaryFacts.at(effectPredicate).empty())
                        actions.emplace(&domain->actions.at(i));
                }
			}
		}
		return actions;
	}

	void Reset() override {};
};


#endif