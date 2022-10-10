#ifndef ConstantDepthFunction_H
#define ConstantDepthFunction_H

#include "../../PDDLTypes/PDDLInstance.hpp"
#include "BaseDepthFunction.h"

using namespace std;

class ConstantDepthFunction : public BaseDepthFunction {
public:
    ConstantDepthFunction(int depth, PDDLInstance instance, double modifier = 1) : ConstantDepth(depth), BaseDepthFunction(instance, modifier) {}
    int GetDepth() override;
private:
    int ConstantDepth = 0;
};

#endif
