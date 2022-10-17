#ifndef PDDL_LITERAL_HH
#define PDDL_LITERAL_HH

#include <vector>

struct PDDLLiteral {
    // Index of domain predicate list
    const unsigned int predicateIndex;
    // What parameter index of action the given argument position refers to
    const std::vector<unsigned int> args;
    // What value the predicate should be with the given arguments
    const bool value;
    PDDLLiteral(unsigned int predicateIndex, std::vector<unsigned int> args, bool value) :
        predicateIndex(predicateIndex), args(args), value(value) {};
};

#endif
