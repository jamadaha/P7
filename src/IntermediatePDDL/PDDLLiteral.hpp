#ifndef PDDL_LITERAL
#define PDDL_LITERAL

#include <string>

#include "PDDLPredicate.hpp"

struct PDDLLiteral {
    PDDLPredicate predicate;
    bool state;
    PDDLLiteral(PDDLPredicate predicate, bool state) : predicate(predicate), state(state) {};
};

#endif
