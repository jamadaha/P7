#include "BaseRegressorReformulator.hh"

#include "../../Regressor/PartialRegressor.hh"
#include "../../Walker/DepthFunctions/ConstantDepthFunction.hh"
#include "../../Walker/WidthFunctions/ConstantWidthFunction.hh"

PDDLInstance BaseRegressorReformulator::ReformulatePDDL(PDDLInstance* instance) {
    bool debugMode = Configs->GetItem<bool>("debugmode");

	PartialRegressor regressor = PartialRegressor(instance, new ConstantDepthFunction(100, instance), new ConstantWidthFunction(100));
	regressor.Regress(&instance->problem->goalState);

    return *instance;
}

SASPlan BaseRegressorReformulator::RebuildSASPlan(PDDLInstance *instance, SASPlan* reformulatedSAS) {

	return *reformulatedSAS;
}