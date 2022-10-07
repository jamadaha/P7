#ifndef PDDL_ARG
#define PDDL_ARG

#include <string>

#include "PDDLType.hpp"

struct PDDLArg {
    int index;
    std::string name;
    PDDLType* typeRef;
    PDDLArg(int index, std::string name, PDDLType* typeRef) : index(index), name(name), typeRef(typeRef) {};
};

#endif
