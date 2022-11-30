#ifndef Partial_REGRESSOR
#define Partial_REGRESSOR

#include "BaseRegressor.hh"

#include "../PDDL/Instance.hh"

#include "PartialActionGenerator/PartialActionGenerator.hh"

class PartialRegressor : public BaseRegressor {
public:
    PartialRegressor(const PDDL::Instance *instance, BaseDepthFunction *depthFunc, BaseWidthFunction *widthFunc) : BaseRegressor(instance, depthFunc, widthFunc) {
        actionGenerator = new PartialActionGenerator(&instance->domain->actions, instance->problem->objects.size());
    };
    ~PartialRegressor() {
        free(actionGenerator);
    }
protected:
    Path RegressFromState(const PDDL::State *state, unsigned int* current) override;
    
private:
    PartialActionGenerator *actionGenerator;
    PartialAction* GetPredecessorStates(std::vector<PartialAction> *actions, std::unordered_set<PDDL::State> &states);
    // Foreach precondition, get which states can lead to it
    // For now it ignores partial parameters
    std::unordered_set<PDDL::State> GetPredecessorStates(const PartialAction *action);
    PDDL::State GeneratePreconditionState(const PDDL::Literal *literal);
    Path ConvertToPath(std::vector<PartialAction> actions);
    void SwitchToNonPartial(std::vector<PartialAction> *actions);
};

#endif
