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
	BaseHeuristics(U context) : Context(context) {}

	virtual T NextChoice(vector<T> choices) = 0;
};

#endif
