#ifndef BaseHeuristics_HH
#define BaseHeuristics_HH

#include <string>
#include <iostream>
#include <vector>

#include "Contexts/BaseContext.h"

template <class T, class U>
class BaseHeuristics {
public:
	U Context;
	std::vector<T> Choices;
	BaseHeuristics(std::vector<T> choices, U context) {
		Choices = choices;
		Context = context;
	}

	virtual T NextChoice() = 0;
};

#endif