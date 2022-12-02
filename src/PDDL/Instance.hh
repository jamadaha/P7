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
        Instance(Domain* domain, Problem* problem, Mutex* mutexes) : domain(domain), problem(problem), mutexes(mutexes) {};
        Instance(Domain* domain, Problem* problem) : domain(domain), problem(problem) {
#ifndef NDEBUG
            SetupDebug();
#endif
        };

#ifndef NDEBUG
        void SetupDebug();
#endif
    };

#ifndef NDEBUG
    extern Instance* CurrentInstance;
#endif
}

#endif
