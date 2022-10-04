#ifndef BaseHeuristics_H
#define BaseHeuristics_H

#include <string>
#include <iostream>
#include <vector>
#include "Contexts/BaseContext.h"

using namespace std;

template <class T, class U>
class BaseHeuristics {
public:
	U Context;
	vector<T> Choices;
	BaseHeuristics(vector<T> choices, U context) {
		Choices = choices;
		Context = context;
	}

	virtual T NextChoice() = 0;
};

#endif