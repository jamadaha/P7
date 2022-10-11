#ifndef PDDL_TYPE
#define PDDL_TYPE

#include <string>

struct PDDLType {
    std::string name;
    PDDLType(std::string name) : name(name) {};
};

#endif
