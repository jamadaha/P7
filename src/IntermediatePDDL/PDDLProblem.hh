#ifndef PDDL_PROBLEM_HH
#define PDDL_PROBLEM_HH

#include <string>
#include <vector>

#include "PDDLDomain.hh"
#include "PDDLState.hh"

struct PDDLProblem {
    const std::string name;
    const PDDLDomain *domain;
    const std::vector<std::string> objects;
    const std::unordered_map<std::string, unsigned int> objectMap;
    const PDDLState initState;
    const PDDLState goalState;
    PDDLProblem() : name("Not Set") {};
    PDDLProblem(std::string name, PDDLDomain *domain, std::vector<std::string> objects, std::unordered_map<std::string, unsigned int> objectMap, PDDLState initState, PDDLState goalState) :
        name(name), domain(domain), objects(objects), objectMap(objectMap), initState(initState), goalState(goalState) {};
};

#endif
