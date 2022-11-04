#include "GreedyHeuristic.hh"

PDDLActionInstance* GreedyHeuristic::NextChoice(PDDLState * state, std::vector<PDDLActionInstance> *choices) const {
    int value = 0;
    std::set<std::string> candidates;
    std::pair<int, std::string> solution;
    std::unordered_map<int, std::string> solutions;


    for(auto obj : this->problem->objects){
        /*Make candidates*/
        candidates.insert(obj);
        /*Find good bester solutions*/
        while(true){
            if (candidates.empty()) break;
            int i = 0;
            for (std::string s : candidates){
                if (/*not in the solution vector*/){
                    /*Calculatings greed for each index*/
                    solutions.emplace(this->Eval(state, i), s);
                }
                ++i;
            }
            /*Add highest pair to solution*/
        }
        /*Sort solutions*/
        /*solution = highest solution*/
    }
    /*return new state at best value (solution)*/
}

int GreedyHeuristic::Eval(const PDDLState *state, int i) const {
    return 1;
}