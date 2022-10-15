#ifndef PDDL_ACTION_HH
#define PDDL_ACTION_HH

#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>

#include "PDDLLiteral.hh"

struct PDDLAction {
    const std::string name;
    const unsigned int parameterCount;
    const std::vector<PDDLLiteral> preconditions;
    const std::vector<PDDLLiteral> effects;
    PDDLAction(std::string name, unsigned int parameterCount, std::vector<PDDLLiteral> preconditions, std::vector<PDDLLiteral> effects) : 
        name(name), parameterCount(parameterCount), preconditions(preconditions), effects(effects) {};
};

#endif
