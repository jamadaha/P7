#ifndef PDDL_MUTEX_INFO
#define PDDL_MUTEX_INFO

#include <string>
#include <vector>

#include "MutexVariable.hh"

namespace PDDL {
    struct Mutex {
        const std::vector<MutexVariable> variables;

        Mutex() {};
        Mutex(std::vector<MutexVariable> variables) : variables(variables) {};

    };
}

#endif
