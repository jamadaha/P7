#include "PartialRegressionReformulator.hh"

#include "../../Regressor/BaseRegressor.hh"
#include "../../Regressor/PartialRegressor.hh"
#include "../../Walker/DepthFunctions/ConstantDepthFunction.hh"
#include "../../Walker/WidthFunctions/ConstantWidthFunction.hh"

std::vector<Path> PartialRegressionReformulator::PerformRegression(PDDLInstance *instance, bool debugMode) {
    PartialRegressor regressor = PartialRegressor(instance, new ConstantDepthFunction(100, instance), new ConstantWidthFunction(100));
	return regressor.Regress();
}