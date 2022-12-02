#ifndef BaseHeuristics_HH
#define BaseHeuristics_HH

#include <string>
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <random>

#include "../../PDDL/Domain.hh"
#include "../../PDDL/Problem.hh"
#include "../../PDDL/Instance.hh"
#include "../../PDDL/ActionInstance.hh"

class BaseHeuristic {
public:
	const PDDL::Domain *domain;
	const PDDL::Problem *problem;
	BaseHeuristic(const PDDL::Domain *domain, const PDDL::Problem *problem) : domain(domain), problem(problem) {
		srand(time(NULL));
	}

	virtual PDDL::ActionInstance* NextChoice(PDDL::State * state, std::vector<PDDL::ActionInstance> *choices) = 0;

	virtual int Eval(const PDDL::State* state, const PDDL::ActionInstance* action = nullptr) const = 0;
	virtual void Reset() = 0;
};

#endif
