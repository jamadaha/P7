#ifndef PDDL_LITERAL_HH
#define PDDL_LITERAL_HH

#include <string>
#include <memory>

#include "PDDLPredicate.hh"
#include "PDDLArg.hh"

struct PDDLLiteral {
    // Reference to the predicate it refers to
    // e.g. :precondition (and (ROOM ?x) (ROOM ?y) (not (= ?x ?y)) (at-robby ?x))
    // A predicate would then be "ROOM", "ROOM", "=", "at-robby"
    // which refers to some predicate of the domain
    PDDLPredicate *predicate;
    // Each ARG refers to the parameter of the given action
    // e.g. ... (ROOM ?y) ... would translate to arg "?y" referring to parameter "?y" of the action
    std::vector<PDDLArg*> args;
    bool state;
    PDDLLiteral(PDDLPredicate *predicate, std::vector<PDDLArg*> args, bool state) : predicate(predicate), args(args), state(state) {};
};

#endif
