#ifndef BaseDepthFunction_HH
#define BaseDepthFunction_HH

#include "../../PDDL/Instance.hh"

class BaseDepthFunction {
public:
    BaseDepthFunction(PDDL::Instance* instance, double modifier = 1) : instance(instance), Modifier(modifier) {
    }
    double Modifier;
    virtual int GetDepth() = 0;
protected:
    PDDL::Instance* instance;
};

#endif