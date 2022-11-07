#include "GreedyHeuristic.hh"
#include "GoalCountHeuristic.hh"
#include <unordered_map>
#include <unordered_set>

PDDLActionInstance* GreedyHeuristic::NextChoice(PDDLState * state, std::vector<PDDLActionInstance> *choices) const {
    int value = 0;
    std::unordered_set<PDDLActionInstance> candidates;
    std::pair<PDDLActionInstance, int> solution;
    PDDLActionInstance *solutionPtr;
    std::unordered_map<PDDLActionInstance, int> solutions;

    for(auto obj : *choices){
        /*Make candidates*/
        candidates.emplace(obj);
        /*Find good bester solutions*/
        int i = 0;
        for (PDDLActionInstance s : candidates){
            if (!solutions.contains(s)){
                /*Calculatings score for each index*/
                solutions.emplace(s, this->Eval(state, i));
            }
            ++i;
        }
        /*Add highest pair to solution*/
        int currentMax = 0;
        PDDLActionInstance currentAction;
        for(auto iter = solutions.cbegin(); iter != solutions.cend(); ++iter){
            if (iter->second > currentMax) {
                currentMax = iter->second; 
                currentAction = iter->first;                
            }
        }
        solution = std::pair<PDDLActionInstance, int>(currentAction, currentMax);
    }
    /*return new state at best value (solution)*/
    solutionPtr = &(solution.first);
    return solutionPtr;
}

int GreedyHeuristic::Eval(const PDDLState *state, int i) const {
    GoalCountHeuristic gch = new GoalCountHeuristic(this->domain, this->problem);
    return gch.Eval(state);
}