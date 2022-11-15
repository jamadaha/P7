#ifndef BASE_REGRESSOR
#define BASE_REGRESSOR

#include <vector>

#include "../IntermediatePDDL/PDDLState.hh"

#include "../Walker/Path.hpp"

#include "../Walker/DepthFunctions/BaseDepthFunction.hh"
#include "../Walker/WidthFunctions/BaseWidthFunction.hh"

class BaseRegressor {
public:
    BaseRegressor(const PDDLInstance *instance, BaseDepthFunction *depthFunc, BaseWidthFunction *widthFunc) : instance(instance), depthFunction(depthFunc), widthFunction(widthFunc) {};
    std::vector<Path> Regress();
    
protected:
    const PDDLInstance *instance;
    BaseDepthFunction *depthFunction;
    BaseWidthFunction *widthFunction;

    virtual Path RegressFromState(const PDDLState *state) = 0;
};

#endif
