#ifndef GreedyHeuristic_HH
#define GreedyHeuristic_HH

#include "BaseHeuristic.hh"
#include <set>

class GreedyHeuristic : public BaseHeuristic {
public:
	GreedyHeuristic(const PDDLDomain *domain, const PDDLProblem *problem) : BaseHeuristic(domain, problem){};

	PDDLActionInstance* NextChoice(PDDLState * state, std::vector<PDDLActionInstance> *choices) const override {
		return ;
	}

	int Eval(const PDDLState *state) const override {
        int value = 0
        std::set<std::string> candidates;
        std::pair<int, std::string> solution;
        std::unordered_map<int, std::string> solutions;


        for(auto obj : this->problem->objects){
            /*Make candidates*/
            candidates.insert(obj);
            /*Find good bester solutions*/
            while(true){
                if (candidates.empty) break;
                for (auto i : candidates){
                    if (/*not in the solution vector*/){
                        /*Calculatings greed for each index*/
                        solutions.enplace(Greed(i), /*id*/);
                    }
                }
                /*Add highest pair to solution*/
            }
            if(solutionValue > value){
                solution = solutionValue;
                value = solutionValue
            }
        }
        return value;
	};

    int Greed(const PDDLState *state) const {
        GoalCountHeuristic gch = GoalCountHeuristic(domain, problem);
    }
};

#endif