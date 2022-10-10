#ifndef RandomHeuristics_H
#define RandomHeuristics_H

using namespace std;

#include <vector>
#include "BaseHeuristics.hh"
#include "Contexts/PDDLContext.h"

template <class T>
class RandomHeuristic : public BaseHeuristics<T, PDDLContext> {
public:
	RandomHeuristic(vector<T> choices, PDDLContext context) : BaseHeuristics<T, PDDLContext>(choices, context){
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