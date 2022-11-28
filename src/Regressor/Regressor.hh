#ifndef REGRESSOR
#define REGRESSOR

#include "BaseRegressor.hh"

#include "../PDDL/Instance.hh"

#include "PartialActionGenerator/PartialActionGenerator.hh"
#include "PartialActionGenerator/PartialActionConverter.hh"

class Regressor : public BaseRegressor {
public:
    struct RegressionStep {
        const PDDL::State state;
        const PDDL::ActionInstance action;
        RegressionStep(PDDL::State state, PDDL::ActionInstance action) : state(state), action(action) {};
    };
    Regressor(const PDDL::Instance *instance, BaseDepthFunction *depthFunc, BaseWidthFunction *widthFunc) :
    BaseRegressor(instance, depthFunc, widthFunc), 
    actionGenerator(PartialActionGenerator(&instance->domain->actions, instance->problem->objects.size())),
    actionConverter(PartialActionConverter(instance)) {};
protected:
    Path RegressFromState(const PDDL::State *state) override;
    
private:
    
    PartialActionGenerator actionGenerator;
    PartialActionConverter actionConverter;
    PDDL::ActionInstance GetLegalPredecessor(const std::vector<PartialAction> *actions, PDDL::State *state, bool *sucess);
};

#endif
