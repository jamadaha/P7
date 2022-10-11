#ifndef PDDL_ACTION_HH
#define PDDL_ACTION_HH

#include <string>
#include <vector>
#include <unordered_map>

#include "PDDLArg.hpp"
#include "PDDLLiteral.hpp"

struct PDDLAction {
    std::string name;
    std::vector<PDDLArg> parameters;
    std::vector<PDDLLiteral> preconditions;
    std::vector<PDDLLiteral> effects;
    PDDLAction() {};
    PDDLAction(std::string name, std::vector<PDDLArg> parameters, std::vector<PDDLLiteral> preconditions, std::vector<PDDLLiteral> effects) :
        name(name), parameters(parameters), preconditions(preconditions), effects(effects) {};
};

#endif
