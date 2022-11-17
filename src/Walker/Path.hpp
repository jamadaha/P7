#ifndef PATH_TYPE
#define PATH_TYPE

#include <vector>

#include "../IntermediatePDDL/PDDLActionInstance.hh"
#include "../IntermediatePDDL/PDDLState.hh"

struct Path {
    mutable PDDLState startState;
    mutable PDDLState endState;
    std::vector<PDDLActionInstance> steps;
    Path(std::vector<PDDLActionInstance> steps) : steps(steps) {};
    Path(std::vector<PDDLActionInstance> steps, PDDLState startState, PDDLState endState) : steps(steps), startState(startState), endState(endState) {};

    friend bool operator==(const Path& lhs, const Path& rhs) {
        return lhs.steps == rhs.steps;
    }
};

#endif
