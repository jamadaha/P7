#ifndef BaseWidthFunction_HH
#define BaseWidthFunction_HH

#include "../../PDDL/Instance.hh"

class BaseWidthFunction {
public:
    const unsigned int max;
    BaseWidthFunction(unsigned int max) : max(max) {};
    virtual bool Iterate(unsigned int *current) = 0;
};

#endif