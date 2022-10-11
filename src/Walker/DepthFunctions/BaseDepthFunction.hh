#ifndef BaseDepthFunction_HH
#define BaseDepthFunction_HH

#include "../../PDDLTypes/PDDLInstance.hpp"

class BaseDepthFunction {
public:
    BaseDepthFunction(double modifier = 1) {
        Modifier = modifier;
    }
    double Modifier;
    virtual int GetDepth(PDDLInstance instance) = 0;
};

#endif