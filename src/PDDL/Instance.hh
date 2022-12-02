#ifndef PDDL_INSTANCE_HH
#define PDDL_INSTANCE_HH

#include "Domain.hh"
#include "Problem.hh"
#include "Mutex.hh"

namespace PDDL {
#ifndef NDEBUG
    extern const Instance* CurrentInstance;
#endif

    class Instance {
    public:
        Domain* domain;
        Problem* problem;
        Mutex* mutexes;
        Instance(Domain* domain, Problem* problem) : domain(domain), problem(problem) {
#ifndef NDEBUG
            CurrentInstance = this;
#endif
        };
    };
}

#endif
