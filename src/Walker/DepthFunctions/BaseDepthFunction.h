#ifndef BaseDepthFunction_H
#define BaseDepthFunction_H

#include "../../PDDLTypes/PDDLInstance.hpp"

using namespace std;

class BaseDepthFunction {
public:
    BaseDepthFunction(PDDLInstance instance, double modifier = 1) : instance(instance), Modifier(modifier) {}
    PDDLInstance instance;
    double Modifier;
    virtual int GetDepth() = 0;
};

#endif
