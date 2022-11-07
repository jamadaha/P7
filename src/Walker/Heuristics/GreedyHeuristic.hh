#ifndef GreedyHeuristic_HH
#define GreedyHeuristic_HH

#include "BaseHeuristic.hh"
#include <set>

class GreedyHeuristic : public BaseHeuristic {
public:
	GreedyHeuristic(const PDDLDomain *domain, const PDDLProblem *problem) : BaseHeuristic(domain, problem){};

	PDDLActionInstance* NextChoice(PDDLState * state, std::vector<PDDLActionInstance> *choices) const override {
		std::unordered_map<PDDLActionInstance*, int> solutions;

		/*Find good bester solutions*/
		for (int i = 0; i < choices->size(); i++) {
			if (!solutions.contains(&choices->at(i))){
				/*Calculatings score for each index*/
				solutions.emplace(&choices->at(i), this->Eval(state));
			}
		}

		/*Add highest pair to solution*/
		int currentMax = -1;
		PDDLActionInstance *currentAction;
		for(auto iter = solutions.begin(); iter != solutions.end(); ++iter){
			if ((*iter).second > currentMax) {
				currentMax = (*iter).second; 
				currentAction = (*iter).first;                
			}
		}

		return currentAction;
	}

    int Eval(const PDDLState *state) const override {
		GoalCountHeuristic gch = GoalCountHeuristic(this->domain, this->problem);
    	return gch.Eval(state);
	}
private:

};

#endif