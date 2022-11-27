#ifndef PATH_TYPE
#define PATH_TYPE

#include <vector>
#include <string>

#include "../PDDL/ActionInstance.hh"
#include "../PDDL/State.hh"
#include "../PDDL/Problem.hh"

class Path {
public:
    const bool hasStates;
    const PDDL::State startState;
    const PDDL::State endState;
    std::vector<PDDL::ActionInstance> steps;
    
    Path(std::vector<PDDL::ActionInstance> steps) : steps(steps), hasStates(false) {};
    Path(std::vector<PDDL::ActionInstance> steps, const PDDL::State startState, const PDDL::State endState) : steps(steps), startState(startState), endState(endState), hasStates(true){};
    Path(const Path &path) : steps(path.steps), startState(path.startState), endState(path.endState), hasStates(path.hasStates) {}

    std::string ToString();
    std::string ToString(const PDDL::Problem *problem);

    friend bool operator==(const Path& lhs, const Path& rhs) {
        return lhs.steps == rhs.steps;
    }
};

#endif
