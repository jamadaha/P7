#ifndef RandomHeuristics_HH
#define RandomHeuristics_HH

#include "BaseHeuristics.hh"

template <class T>
class RandomHeuristic : public BaseHeuristics<T> {
public:
	RandomHeuristic() : BaseHeuristics<T>(nullptr, nullptr){
		// 0 for debugging purposes
		srand(0);
		//srand(time(NULL));
	};

	int Eval(const PDDLState *state) const override {
		return rand();
	};
};

#endif