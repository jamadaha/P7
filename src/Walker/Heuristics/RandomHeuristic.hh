#ifndef RandomHeuristic_HH
#define RandomHeuristic_HH

#include "BaseHeuristic.hh"

class RandomHeuristic : public BaseHeuristic {
public:
	RandomHeuristic() : BaseHeuristic(nullptr, nullptr){};

	PDDLActionInstance* NextChoice(PDDLState * state, std::vector<PDDLActionInstance> *choices) override {
		return &choices->at(rand() % choices->size());
	}

	int Eval(const PDDLState *state) const override {
		return rand();
	};
};

#endif
