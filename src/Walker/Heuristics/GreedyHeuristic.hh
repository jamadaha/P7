#ifndef GreedyHeuristic_HH
#define GreedyHeuristic_HH

#include "BaseHeuristic.hh"
#include <set>

class GreedyHeuristic : public BaseHeuristic {
public:
	GreedyHeuristic(const PDDLDomain *domain, const PDDLProblem *problem) : BaseHeuristic(domain, problem){};

	PDDLActionInstance* NextChoice(PDDLState * state, std::vector<PDDLActionInstance> *choices) const override {
		std::pair<PDDLActionInstance*, int> solution;
		std::unordered_map<PDDLActionInstance*, int> solutions;

		/*Find good bester solutions*/
		for (auto iter = choices->begin(); iter != choices->end(); iter++){
			if (!solutions.contains(&(*iter))){
				/*Calculatings score for each index*/
				solutions.emplace(&(*iter), this->Eval(state));
			}
		}

		/*Add highest pair to solution*/
		unsigned int currentMax = 0;
		PDDLActionInstance *currentAction;
		for(auto iter = solutions.begin(); iter != solutions.end(); ++iter){
			if (iter->second > currentMax) {
				currentMax = iter->second; 
				currentAction = iter->first;                
			}
		}

		solution = std::pair<PDDLActionInstance*, int>(currentAction, currentMax);
		return solution.first;
	}

    int Eval(const PDDLState *state) const override {
		GoalCountHeuristic gch = GoalCountHeuristic(this->domain, this->problem);
    	return gch.Eval(state);
	}
private:

};

#endif