#ifndef BaseHeuristics_H
#define BaseHeuristics_H

#include <string>
#include <iostream>
#include <vector>

using namespace std;

template <class T>
class BaseHeuristics {
public:
	vector<T> Choices;
	BaseHeuristics(vector<T> choices) {
		Choices = choices;
	}

	virtual T NextChoice() = 0;
};

#endif