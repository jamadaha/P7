#ifndef ObjectActionDepthFunction_H
#define ObjectActionDepthFunction_H

#include "../../PDDLTypes/PDDLInstance.hpp"
#include "BaseDepthFunction.h"

using namespace std;

class ObjectActionDepthFunction : public BaseDepthFunction {
public:
    ObjectActionDepthFunction(PDDLInstance instance, double modifier = 1) : BaseDepthFunction(instance, modifier) {}
    int GetDepth() override;
};

#endif
