#ifndef RandomHeuristic_HH
#define RandomHeuristic_HH

#include "BaseHeuristic.hh"

class RandomHeuristic : public BaseHeuristic {
public:
	RandomHeuristic(bool isDebug) : BaseHeuristic(nullptr, nullptr){
		// 0 for debugging purposes
		if (isDebug)
			srand(0);
		else
			srand(time(NULL));
	};

	PDDLActionInstance* NextChoice(PDDLState * state, std::vector<PDDLActionInstance> *choices) const override {
		return &choices->at(rand() % choices->size());
	}

	int Eval(const PDDLState *state) const override {
		return rand();
	};
};

#endif
