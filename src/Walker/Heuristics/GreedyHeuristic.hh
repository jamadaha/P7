#ifndef GreedyHeuristic_HH
#define GreedyHeuristic_HH

#include "BaseHeuristic.hh"
#include <set>

class GreedyHeuristic : public BaseHeuristic {
public:
	GreedyHeuristic(const PDDLDomain *domain, const PDDLProblem *problem) : BaseHeuristic(domain, problem){};

	PDDLActionInstance* NextChoice(PDDLState * state, std::vector<PDDLActionInstance> *choices) const;
private:
    int Eval(const PDDLState *state) const override; /*std::unordered_map<int, std::string> solutions*/
};

#endif