#ifndef PDDL_ARG_HH
#define PDDL_ARG_HH

#include <string>

#include "PDDLType.hh"

struct PDDLArg {
    int index;
    std::string name;
    PDDLType* typeRef;
    PDDLArg(int index, std::string name, PDDLType* typeRef) : index(index), name(name), typeRef(typeRef) {};
};

#endif
