#ifndef PDDL_INSTANCE_HH
#define PDDL_INSTANCE_HH

#include "Domain.hh"
#include "Problem.hh"
#include "Mutex.hh"

namespace PDDL {
    class Instance {
    public:
        Domain* domain;
        Problem* problem;
        Mutex* mutexes;
        Instance(Domain* domain, Problem* problem) : domain(domain), problem(problem) {};
    };
}

#endif
