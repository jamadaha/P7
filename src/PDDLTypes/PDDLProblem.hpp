#ifndef PDDL_PROBLEM
#define PDDL_PROBLEM

#include <string>
#include <vector>

#include "../PDDLParser/problem.hh"
#include "PDDLArg.hpp"
#include "PDDLLiteral.hpp"
#include "PDDLPredicate.hpp"
#include "PDDLDomain.hpp"
#include "PDDLState.hpp"

class PDDLProblem {
public:
    std::string name;
    PDDLDomain *domain;

    std::vector<std::string> objects;
    PDDLState initState;
    PDDLState goalState;

    PDDLProblem(Problem* problem, PDDLDomain *_domain) : name(problem->_name), domain(_domain) {
        for (auto const& object : *problem->_objects)
            objects.push_back(object);
        
        for (auto const& init : *problem->_init) {
            std::vector<PDDLArg> args = domain->GetArguments(init->first->_args, init->first->_types);
            initState.state.push_back(PDDLLiteral(PDDLPredicate(init->first->_name, args), init->second));
        }
            
        for (auto const& goal : *problem->_goal) {
            std::vector<PDDLArg> args = domain->GetArguments(goal->first->_args, goal->first->_types);
            goalState.state.push_back(PDDLLiteral(PDDLPredicate(goal->first->_name, args), goal->second));
        }
        initState.objects = &objects;
        goalState.objects = &objects;
    }
private:
};

#endif
