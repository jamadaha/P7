#ifndef PREVIOUS_BASE_HEURISTIC
#define PREVIOUS_BASE_HEURISTIC

#include "BaseHeuristic.hh"

class PreviousBaseHeuristic : public BaseHeuristic {
public:
	PreviousBaseHeuristic(const PDDLDomain* domain, const PDDLProblem* problem) : BaseHeuristic(domain, problem) {};

	PDDLActionInstance* NextChoice(PDDLState* state, std::vector<PDDLActionInstance>* choices) override {
		PDDLActionInstance* validChoice;
		for (int i = 0; i < choices->size(); i++) {
			int index = rand() % choices->size();
			PDDLActionInstance selectedChoice = choices->at(index);
			bool contains = false;
			for (auto choice : PreviousActions)
			{
				if (selectedChoice == choice) {
					contains = true;
					break;
				}
			}
			if (!contains || i == choices->size() - 1) {
				validChoice = &choices->at(index);
				break;
			}
		}
		PreviousActions.clear();
		PreviousActions = *choices;
		return validChoice;
	}

	int Eval(const PDDLState* state) const override {
		return 0;
	};

private:
	std::vector<PDDLActionInstance> PreviousActions;
};


#endif