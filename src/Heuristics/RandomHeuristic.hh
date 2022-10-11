#ifndef RandomHeuristics_HH
#define RandomHeuristics_HH

#include <vector>

#include "BaseHeuristics.hh"
#include "Contexts/PDDLContext.hh"

template <class T>
class RandomHeuristic : public BaseHeuristics<T, PDDLContext> {
public:
	RandomHeuristic(std::vector<T> choices, PDDLContext context) : BaseHeuristics<T, PDDLContext>(choices, context){
		srand(time(NULL));
	}
	T NextChoice() override;
};

template <class T>
T RandomHeuristic<T>::NextChoice() {
	if (this->Choices.size() == 0)
		return T();
	int rndNum = rand() % this->Choices.size();
	return this->Choices[rndNum];
}

#endif