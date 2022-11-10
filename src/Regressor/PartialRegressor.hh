#ifndef Partial_REGRESSOR
#define Partial_REGRESSOR

#include "BaseRegressor.hh"

#include "../IntermediatePDDL/PDDLInstance.hh"

#include "PartialActionGenerator/PartialActionGenerator.hh"

class PartialRegressor : BaseRegressor {
public:
    PartialRegressor(const PDDLInstance *instance, BaseDepthFunction *depthFunc, BaseWidthFunction *widthFunc) : BaseRegressor(instance, depthFunc, widthFunc) {};
    std::vector<Path> Regress(const PDDLState *state) override;
    
private:
    // Foreach precondition, get which states can lead to it
    // For now it ignores partial parameters
    std::unordered_set<PDDLState> GetPredecessorStates(const PartialAction *action);
    PDDLState GeneratePreconditionState(const PDDLLiteral *literal);
};

#endif
