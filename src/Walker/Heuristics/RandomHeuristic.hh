#ifndef RandomHeuristics_H
#define RandomHeuristics_H

using namespace std;

#include <vector>
#include "BaseHeuristics.hh"
#include "Contexts/PDDLContext.h"

template <class T>
class RandomHeuristic : public BaseHeuristics<T, PDDLContext> {
public:
	RandomHeuristic(PDDLContext context) : BaseHeuristics<T, PDDLContext>(context){
		srand(time(NULL));
	}
	T NextChoice(vector<T> choices) override;
};

template <class T>
T RandomHeuristic<T>::NextChoice(vector<T> choices) {
	int rndNum = rand() % choices.size();
	return choices[rndNum];
}

#endif