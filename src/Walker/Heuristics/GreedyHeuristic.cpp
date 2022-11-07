#include "GreedyHeuristic.hh"
#include "GoalCountHeuristic.hh"
#include <unordered_map>
#include <unordered_set>

PDDLActionInstance* GreedyHeuristic::NextChoice(PDDLState * state, std::vector<PDDLActionInstance> *choices) const {
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

int GreedyHeuristic::Eval(const PDDLState *state) const {
    GoalCountHeuristic gch = GoalCountHeuristic(this->domain, this->problem);
    return gch.Eval(state);
}