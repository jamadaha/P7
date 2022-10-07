#ifndef ObjectActionDepthFunction_H
#define ObjectActionDepthFunction_H

#include "../PDDLTypes/PDDLInstance.hpp"
#include "BaseDepthFunction.h"

using namespace std;

class ObjectActionDepthFunction : public BaseDepthFunction {
public:
    ObjectActionDepthFunction(double modifier = 1) : BaseDepthFunction(modifier) {}
    int GetDepth(PDDLInstance instance) override;
};

#endif
