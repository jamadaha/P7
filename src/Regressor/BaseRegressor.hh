#ifndef BASE_REGRESSOR
#define BASE_REGRESSOR

#include <vector>

#include "../PDDL/State.hh"

#include "../Walker/Path.hh"

#include "../Walker/DepthFunctions/BaseDepthFunction.hh"
#include "../Walker/WidthFunctions/BaseWidthFunction.hh"

class BaseRegressor {
public:
    BaseRegressor(const PDDL::Instance *instance, BaseDepthFunction *depthFunc, BaseWidthFunction *widthFunc) : instance(instance), depthFunction(depthFunc), widthFunction(widthFunc) {};
    std::vector<Path> Regress();
    
protected:
    const PDDL::Instance *instance;
    BaseDepthFunction *depthFunction;
    BaseWidthFunction *widthFunction;

    virtual Path RegressFromState(const PDDL::State *state, unsigned int *current) = 0;
    void GetPredecessorState(PDDL::State *state, const PDDL::ActionInstance *action);
};

#endif
