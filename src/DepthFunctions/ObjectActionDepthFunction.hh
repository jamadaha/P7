#ifndef ObjectActionDepthFunction_HH
#define ObjectActionDepthFunction_HH

#include "../PDDLTypes/PDDLInstance.hpp"
#include "BaseDepthFunction.hh"

class ObjectActionDepthFunction : public BaseDepthFunction {
public:
    ObjectActionDepthFunction(double modifier = 1) : BaseDepthFunction(modifier) {}
    int GetDepth(PDDLInstance instance) override;
};

#endif
