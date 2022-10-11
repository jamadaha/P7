#ifndef ConstantDepthFunction_HH
#define ConstantDepthFunction_HH

#include "../PDDLTypes/PDDLInstance.hpp"
#include "BaseDepthFunction.hh"

class ConstantDepthFunction : public BaseDepthFunction {
public:
    ConstantDepthFunction(int depth, double modifier = 1) : ConstantDepth(depth), BaseDepthFunction(modifier) {}
    int GetDepth(PDDLInstance instance) override;
private:
    int ConstantDepth = 0;
};

#endif
