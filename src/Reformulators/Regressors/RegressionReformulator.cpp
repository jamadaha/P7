#include "RegressionReformulator.hh"

#include "../../Regressor/BaseRegressor.hh"
#include "../../Regressor/Regressor.hh"
#include "../../Walker/DepthFunctions/ConstantDepthFunction.hh"
#include "../../Walker/WidthFunctions/ConstantWidthFunction.hh"
#include "../../Walker/WidthFunctions/TimeWidthFunction.hh"

std::vector<Path> RegressionReformulator::PerformRegression(PDDLInstance *instance, bool debugMode) {
    Regressor regressor = Regressor(instance, new ConstantDepthFunction(100, instance), new TimeWidthFunction(TimeLimit));
	return regressor.Regress();
}