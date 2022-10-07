#ifndef BaseDepthFunction_H
#define BaseDepthFunction_H

#include "../PDDLTypes/PDDLInstance.hpp"

using namespace std;

class BaseDepthFunction {
public:
    BaseDepthFunction(double modifier = 1) {
        Modifier = modifier;
    }
    double Modifier;
    virtual int GetDepth(PDDLInstance instance) = 0;
};

#endif
