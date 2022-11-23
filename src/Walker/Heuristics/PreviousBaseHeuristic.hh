#ifndef PREVIOUS_BASE_HEURISTIC
#define PREVIOUS_BASE_HEURISTIC

#include "BaseHeuristic.hh"
#include <unordered_set>

class PreviousBaseHeuristic : public BaseHeuristic {
public:
	PreviousBaseHeuristic(const PDDLDomain* domain, const PDDLProblem* problem) : BaseHeuristic(domain, problem) {
		baseHeuristic = new GoalPredicateCountHeuristic(domain, problem);
	};
	~PreviousBaseHeuristic() {
		free(baseHeuristic);
	}

	PDDLActionInstance* NextChoice(PDDLState* state, std::vector<PDDLActionInstance>* choices) override {
		std::vector<PDDLActionInstance> newChoices;
		for (auto choice = choices->begin(); choice != choices->end(); choice++) {
			if (PreviousActions.contains(*choice))
				newChoices.push_back(*choice);
		}
		if (newChoices.size() != 0)
			return baseHeuristic->NextChoice(state, &newChoices);
		else
			return baseHeuristic->NextChoice(state, choices);
	}

	int Eval(const PDDLState* state) const override {
		return 0;
	};

private:
	BaseHeuristic* baseHeuristic;
	std::unordered_set<PDDLActionInstance> PreviousActions;
};


#endif