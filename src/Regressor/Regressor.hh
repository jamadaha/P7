#ifndef REGRESSOR
#define REGRESSOR

#include "BaseRegressor.hh"

#include "../IntermediatePDDL/PDDLInstance.hh"

#include "PartialActionGenerator/PartialActionGenerator.hh"
#include "PartialActionGenerator/PartialActionConverter.hh"

class Regressor : public BaseRegressor {
public:
    struct RegressionStep {
        const PDDLState state;
        const PDDLActionInstance action;
        RegressionStep(PDDLState state, PDDLActionInstance action) : state(state), action(action) {};
    };
    Regressor(const PDDLInstance *instance, BaseDepthFunction *depthFunc, BaseWidthFunction *widthFunc) : 
    BaseRegressor(instance, depthFunc, widthFunc), 
    actionGenerator(PartialActionGenerator(&instance->domain->actions, instance->problem->objects.size())),
    actionConverter(PartialActionConverter(instance)) {};
protected:
    Path RegressFromState(const PDDLState *state) override;
    
private:
    
    PartialActionGenerator actionGenerator;
    PartialActionConverter actionConverter;
    PDDLActionInstance GetLegalPredecessor(const std::vector<PartialAction> *actions, PDDLState *state, bool *sucess);
};

#endif
