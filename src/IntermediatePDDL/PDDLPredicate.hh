#ifndef PDDL_PREDICATE_HH
#define PDDL_PREDICATE_HH

#include <string>
#include <vector>

struct PDDLPredicate {
    const std::string name;
    const int argumentCount;
    
    PDDLPredicate(std::string name, int argumentCount) : name(name), argumentCount(argumentCount) {}
};

#endif
