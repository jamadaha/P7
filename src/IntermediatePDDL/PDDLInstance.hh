#ifndef PDDL_INSTANCE_HH
#define PDDL_INSTANCE_HH

#include "PDDLDomain.hh"
#include "PDDLProblem.hh"
#include "PDDLMutex.hh"

class PDDLInstance {
public:
    PDDLDomain *domain;
    PDDLProblem *problem;
    PDDLMutex *mutexes;
    PDDLInstance(PDDLDomain* domain, PDDLProblem* problem) : domain(domain), problem(problem) {};
};

#endif
