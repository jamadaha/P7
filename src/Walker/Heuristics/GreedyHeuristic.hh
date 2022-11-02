#ifndef GreedyHeuristic_HH
#define GreedyHeuristic_HH

#include "BaseHeuristic.hh"
#include <set>

class GreedyHeuristic : public BaseHeuristic {
public:
	GreedyHeuristic(const PDDLDomain *domain, const PDDLProblem *problem) : BaseHeuristic(domain, problem){};

	PDDLActionInstance* NextChoice(PDDLState * state, std::vector<PDDLActionInstance> *choices) const override {
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
                        solutions.enplace(this.Eval(i, solutions), /*id*/);
                    }
                }
                /*Add highest pair to solution*/
            }
            /*Sort solutions*/
            /*solution = highest solution*/
        }
        /*return new state at best value (solution)*/
	}

	int Eval(const PDDLState *state, /*std::unordered_map<int, std::string> solutions*/) const override {
	};
};

#endif


/* Christoffer fik maksimal head explosion af C++, så her er pseudokoden

procedure Greedy-Search : State x Actions -> State
    let value = 0
    let candidates be a list
    let solution be a (Int, String) tuple
    let solutions be a (Int, String) map

    for each object o in the State problem domain do:
        candidates.insert(o)
        do
            if candidates = empty
            then break 
            else
            for each string id in candidates do:
                if the candidate is not already in the solution vector then
                    let greed = call Greed-Score(candidate with id, solutions)
                    solutions.push( (greed, id) )
            sort solutions
            let solution = highest in solutions
        while(true)

        return state with highest greed value

sub-procedure Greedy-Score : State x States -> Int
        sum = 0, greed = 0
        let gch be the goal count heuristic

        For each (i, s) in States do
            sum += gch(s)
        
        return gch(State) / sum - gch(State)
*/