#ifndef PDDL_ACTION
#define PDDL_ACTION

#include <string>
#include <vector>

#include "PDDLArg.hpp"
#include "PDDLLiteral.hpp"

struct PDDLAction {
    std::string name;
    std::vector<PDDLArg> parameters;
    std::vector<PDDLLiteral> preconditions;
    std::vector<PDDLLiteral> effects;
};

#endif
