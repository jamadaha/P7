#ifndef PREVIOUS_BASE_HEURISTIC
#define PREVIOUS_BASE_HEURISTIC

#include "BaseHeuristic.hh"
#include <unordered_set>

class PreviousBaseHeuristic : public BaseHeuristic {
public:
	PreviousBaseHeuristic(const PDDL::Domain* domain, const PDDL::Problem* problem) : BaseHeuristic(domain, problem) {
		baseHeuristic = new GoalPredicateCountHeuristic(domain, problem);
		isFirstSet = false;
	};
	~PreviousBaseHeuristic() {
		free(baseHeuristic);
	}

	PDDL::ActionInstance* NextChoice(PDDL::State* state, std::vector<PDDL::ActionInstance>* choices) override {
		if (!isFirstSet) {
			isFirstSet = true;
			PreviousActions.clear();
			for (auto choice = choices->begin(); choice != choices->end(); choice++) {
				PreviousActions.emplace(*choice);
			}
			return baseHeuristic->NextChoice(state, choices);
		}
		else {
			std::vector<PDDL::ActionInstance> newChoices;
			for (auto choice = choices->begin(); choice != choices->end(); choice++) {
				if (!PreviousActions.contains(*choice))
					newChoices.push_back(*choice);
			}
			if (newChoices.size() != 0) {
				choices->clear();
				PreviousActions.clear();
				for (auto choice : newChoices) {
					choices->push_back(choice);
					PreviousActions.emplace(choice);
				}
				return baseHeuristic->NextChoice(state, choices);
			}
			else
				return baseHeuristic->NextChoice(state, choices);
		}
	}

	int Eval(const PDDL::State* state) const override {
		return 0;
	};

private:
	BaseHeuristic* baseHeuristic;
	std::unordered_set<PDDL::ActionInstance> PreviousActions;
	bool isFirstSet = false;

	void Reset() override {
		isFirstSet = false;
	}
};


#endif