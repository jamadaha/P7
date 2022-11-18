#ifndef PATH_TYPE
#define PATH_TYPE

#include <vector>
#include <string>

#include "../IntermediatePDDL/PDDLActionInstance.hh"
#include "../IntermediatePDDL/PDDLState.hh"

class Path {
public:
    const bool hasStates;
    const PDDLState startState;
    const PDDLState endState;
    std::vector<PDDLActionInstance> steps;
    
    Path(std::vector<PDDLActionInstance> steps) : steps(steps), hasStates(false) {};
    Path(std::vector<PDDLActionInstance> steps, const PDDLState startState, const PDDLState endState) : steps(steps), startState(startState), endState(endState), hasStates(true){};
    Path(const Path &path) : steps(path.steps), startState(path.startState), endState(path.endState), hasStates(path.hasStates) {}

    std::string ToString();

    friend bool operator==(const Path& lhs, const Path& rhs) {
        return lhs.steps == rhs.steps;
    }
};

#endif
