#ifndef RandomHeuristics_H
#define RandomHeuristics_H

using namespace std;

#include <vector>
#include "BaseHeuristics.hh"

template <class T>
class RandomHeuristic : public BaseHeuristics<T> {
public:
	RandomHeuristic(vector<T> choices) : BaseHeuristics<T>(choices){
		srand(time(NULL));
	}
	T NextChoice() override;
};

template <class T>
T RandomHeuristic<T>::NextChoice() {
	int rndNum = rand() % this->Choices.size();
	return this->Choices[rndNum];
}

#endif