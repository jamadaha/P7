#ifndef PATH_TYPE
#define PATH_TYPE

#include <vector>

#include "../IntermediatePDDL/PDDLActionInstance.hh"
#include "../IntermediatePDDL/PDDLState.hh"

struct Path {
    std::vector<PDDLState> states;
    std::vector<PDDLActionInstance> steps;
    Path(std::vector<PDDLActionInstance> steps) : steps(steps) {};
    Path(std::vector<PDDLActionInstance> steps, std::vector<PDDLState> states) : steps(steps), states(states) {};
    Path(const Path &path) : steps(path.steps) {};

    friend bool operator==(const Path& lhs, const Path& rhs) {
        return lhs.steps == rhs.steps;
    }
};

#endif
