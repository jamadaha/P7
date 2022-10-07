#ifndef PDDL_ARG
#define PDDL_ARG

#include <string>

#include "PDDLType.hpp"

struct PDDLArg {
    std::string name;
    PDDLType* typeRef;
    PDDLArg(std::string name, PDDLType* typeRef) : name(name), typeRef(typeRef) {};
};

#endif
