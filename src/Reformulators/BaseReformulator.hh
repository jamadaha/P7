#ifndef BaseReformulator_HH
#define BaseReformulator_HH

#include "../IntermediatePDDL/PDDLInstance.hh"
#include "../SAS/Plan.hh"
#include "../Config/Config.hh"
#include "../RunReport/RunReport.hh"

class BaseReformulator {
public:
	int TimeLimit = 1000;
	int Iteration = 1;
	int ReportID = -1;
	int GetMacrosGenerated() { return macrosGenerated; };
	bool DidEncounterErrors() { return encounteredErrors; };
	BaseReformulator(Config* config, RunReport* report) : Configs(config), Report(report) {

	}

	virtual PDDLInstance ReformulatePDDL(PDDLInstance* instance) = 0;
	virtual SAS::Plan RebuildSASPlan(PDDLInstance *instance, SAS::Plan* reformulatedSAS) = 0;
protected:
	Config* Configs;
	RunReport* Report;
	const int debugIndent = 2;
	int macrosGenerated = 0;
	bool encounteredErrors = false;
};

#endif