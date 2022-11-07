#ifndef GOAL_PREDICATE_COUNT_HEURISTIC
#define GOAL_PREDICATE_COUNT_HEURISTIC

#include <unordered_set>
#include "BaseHeuristic.hh"

//https://stackoverflow.com/questions/28367913/how-to-stdhash-an-unordered-stdpair
namespace std {
	template <class T>
	inline void hash_combine(std::size_t& seed, const T& v)
	{
		std::hash<T> hasher;
		seed ^= hasher(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
	}

	template<typename T1, typename T2>
	struct hash<std::pair<T1, T2>> {
		std::size_t operator()(std::pair<T1, T2> const &p) const {
		std::size_t seed1(0);
		std::hash_combine(seed1, p.first);
		std::hash_combine(seed1, p.second);

		std::size_t seed2(0);
		std::hash_combine(seed2, p.second);
		std::hash_combine(seed2, p.first);

		return std::min(seed1, seed2);
		}
	};
}

class GoalPredicateCountHeuristic : public BaseHeuristic {
public:
	GoalPredicateCountHeuristic(const PDDLDomain *domain, const PDDLProblem *problem) : BaseHeuristic(domain, problem){
		GenerateGoalPredicates();
	};

	PDDLActionInstance* NextChoice(PDDLState * state, std::vector<PDDLActionInstance> *choices) const override {
		int bestIndex = -1;
		int bestValue = -1;
		auto engine = std::default_random_engine{};

		// The purpose of this init bullshitery is making it take random choices in case of equal values
		int init = rand() % choices->size();
		int i = init + 1;
	
		while (i != init) {
			i++;
			if (i >= choices->size()) {
				i = 0;
			}

			state->DoAction(&choices->at(i));
			int value = Eval(state);
			state->UndoAction(&choices->at(i));
			if (value >= bestValue) {
				bestIndex = i;
				bestValue = value;
			}
		}

		return &choices->at(bestIndex);
	}

	int Eval(const PDDLState *state) const override {
		int value = 0;
		for (auto iter = problem->goalState.unaryFacts.begin(); iter != problem->goalState.unaryFacts.end(); iter++)
			for (auto factIter = (*iter).second.begin(); factIter != (*iter).second.end(); factIter++)
				if (state->ContainsFact((*iter).first, &(*factIter)))
					value += 1000;
		for (auto iter = problem->goalState.multiFacts.begin(); iter != problem->goalState.multiFacts.end(); iter++)
			for (auto factIter = (*iter).second.begin(); factIter != (*iter).second.end(); factIter++)
				if (state->ContainsFact((*iter).first, &(*factIter)))
					value += 1000;
		for (auto iter = goalPreconditions.begin(); iter != goalPreconditions.end(); iter++) {
			if (domain->predicates.at((*iter)).arguments.size() == 1)
				value += state->unaryFacts.at((*iter)).size();
			else
				value += 2 * state->multiFacts.at((*iter)).size();
		}
		
		return value;
	};
private:
	// The preconditions of actions which has an effect relating to goal state
	// e.g. goal: ball at some room - actions: drop - preconditions: holding ball & at-room 
	// Is a set as the case of same predicate different values is still valid
	std::unordered_set<unsigned int> goalPreconditions;

	void GenerateGoalPredicates() {
		std::unordered_set<const PDDLAction*> actions = GetRelevantActions();
		for (auto action = actions.begin(); action != actions.end(); action++) {
			for (int i = 0; i < (*action)->preconditions.size(); i++) {
				const PDDLLiteral *literal = &(*action)->preconditions.at(i);
				goalPreconditions.emplace(literal->predicateIndex);
			}
		}
	}

	// Retries those PDDLAction whose effect relates to the goal state
	// TODO: Handle cases where goal state requires something to be false
	std::unordered_set<const PDDLAction*> GetRelevantActions() {
		std::unordered_set<const PDDLAction*> actions;
		for (int i = 0; i < domain->actions.size(); i++) {
			const PDDLAction *action = &domain->actions.at(i);
			for (int eff = 0; eff < action->effects.size(); eff++) {
				const PDDLLiteral *effect = &action->effects.at(eff);
				bool containsEffectFact = (problem->goalState.unaryFacts.contains(effect->predicateIndex) && problem->goalState.unaryFacts.at(effect->predicateIndex).size() > 0
				|| problem->goalState.multiFacts.contains(effect->predicateIndex) && problem->goalState.multiFacts.at(effect->predicateIndex).size() > 0);
				if (effect->value && containsEffectFact)
					actions.emplace(action);
			}
		}
		return actions;
	}
};


#endif