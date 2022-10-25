#ifndef BaseHeuristics_HH
#define BaseHeuristics_HH

#include <string>
#include <iostream>
#include <vector>
#include <set>

#include "../../IntermediatePDDL/PDDLDomain.hh"
#include "../../IntermediatePDDL/PDDLProblem.hh"
#include "../../IntermediatePDDL/PDDLInstance.hh"

class BaseHeuristic {
public:
	const PDDLDomain *domain;
	const PDDLProblem *problem;
	BaseHeuristic(const PDDLDomain *domain, const PDDLProblem *problem) : domain(domain), problem(problem) {}

	virtual PDDLActionInstance* NextChoice(const PDDLState * state, std::vector<PDDLActionInstance> *choices) const = 0; /*{
		int maxIndex = -1;
		int maxValue;
		for (int i = 0; i < choices->size(); i++) {
			int value = 0;//Eval(choices.at(i));
			if (maxIndex == -1) {
				maxIndex = i;
				maxValue = value;
			} else if (value > maxValue) {
				maxIndex = i;
				maxValue = value;
			}
		}
		return &(choices->at(maxIndex));
	};*/

	virtual int Eval(const PDDLState *state) const = 0;
};

#endif
