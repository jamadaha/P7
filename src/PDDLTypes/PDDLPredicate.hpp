#ifndef PDDL_PREDICATE
#define PDDL_PREDICATE

#include <string>
#include <vector>

#include "PDDLArg.hpp"

struct PDDLPredicate {
    std::string name;
    std::vector<PDDLArg> args;
    PDDLPredicate(std::string name, std::vector<PDDLArg> args) : name(name), args(args) {};
};

#endif
