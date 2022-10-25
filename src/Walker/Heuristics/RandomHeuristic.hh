#ifndef RandomHeuristic_HH
#define RandomHeuristic_HH

#include "BaseHeuristics.hh"

class RandomHeuristic : public BaseHeuristics {
public:
	RandomHeuristic() : BaseHeuristics(nullptr, nullptr){
		// 0 for debugging purposes
		srand(0);
		//srand(time(NULL));
	};

	int Eval(const PDDLState *state) const override {
		return rand();
	};
};

#endif