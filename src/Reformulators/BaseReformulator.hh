#ifndef BaseReformulator_HH
#define BaseReformulator_HH

#include "../IntermediatePDDL/PDDLInstance.hh"
#include "../SASParser/SASParser.hh"
#include "../Config/Config.hh"
#include "../RunReport/RunReport.hh"

class BaseReformulator {
public:
	int TimeLimit = 1000;
	BaseReformulator(Config* config) : Configs(config) {

	}

	virtual PDDLInstance ReformulatePDDL(PDDLInstance* instance) = 0;
	virtual SASPlan RebuildSASPlan(PDDLInstance *instance, SASPlan* reformulatedSAS) = 0;
protected:
	Config* Configs;
};

#endif