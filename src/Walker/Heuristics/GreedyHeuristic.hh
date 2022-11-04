#ifndef GreedyHeuristic_HH
#define GreedyHeuristic_HH

#include "BaseHeuristic.hh"
#include <set>

class GreedyHeuristic : public BaseHeuristic {
public:
	GreedyHeuristic(const PDDLDomain *domain, const PDDLProblem *problem) : BaseHeuristic(domain, problem){};

	PDDLActionInstance* NextChoice(PDDLState * state, std::vector<PDDLActionInstance> *choices) const override;
private:
    int Eval(const PDDLState *state, int i) const; /*std::unordered_map<int, std::string> solutions*/
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
        sum = ⍺⊂⊂⊂⊂, greed = 0
        let gch be the goal count heuristic

        For each (i, s) in States do
            sum += gch(s)
        
        return gch(State) / sum - gch(State)
*/