#ifndef PDDL_INSTANCE
#define PDDL_INSTANCE

#include "PDDLDomain.hpp"
#include "PDDLProblem.hpp"

class PDDLInstance {
public:
    PDDLDomain* domain;
    PDDLProblem* problem;
    PDDLInstance(PDDLDomain* domain, PDDLProblem* problem) : domain(domain), problem(problem) {};
};

#endif
