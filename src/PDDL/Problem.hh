#ifndef PDDL_PROBLEM_HH
#define PDDL_PROBLEM_HH

#include <string>
#include <vector>

#include "Domain.hh"
#include "State.hh"

namespace PDDL {
    struct Problem {
        const std::string name;
        const Domain* domain;
        const std::vector<std::string> objects;
        const std::unordered_map<std::string, unsigned int> objectMap;
        const State initState;
        const State goalState;
        Problem() : name("Not Set") {};
        Problem(std::vector<std::string> objects) : name("Only Objects"), objects(objects) {};
        Problem(std::string name, PDDL::Domain* domain, std::vector<std::string> objects, std::unordered_map<std::string, unsigned int> objectMap, PDDL::State initState, PDDL::State goalState) :
            name(name), domain(domain), objects(objects), objectMap(objectMap), initState(initState), goalState(goalState) {};
    };
}

#endif
