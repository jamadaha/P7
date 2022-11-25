#ifndef BaseReformulator_HH
#define BaseReformulator_HH

#include "../IntermediatePDDL/PDDLInstance.hh"
#include "../SASParser/SASParser.hh"
#include "../Config/Config.hh"
#include "../RunReport/RunReport.hh"

#include "../EntanglementFinder/EntanglementFinder.hh"
#include "../EntanglementFinder/EntanglementOccurance.hh"
#include "../EntanglementFinder/EntanglementEvaluator.hh"
#include "../EntanglementFinder/EntanglementEvaluatorModifiers.hh"

#include "../MacroGenerator/MacroGenerator.hh"
#include "../MacroGenerator/InstanceGenerator.hh"

#include "../Helpers/ProgressBarHelper.hh"

#include "../MacroVerifyer/MacroVerifyer.hh"

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
	virtual SASPlan RebuildSASPlan(PDDLInstance *instance, SASPlan* reformulatedSAS);
protected:
	Config* Configs;
	RunReport* Report;
	const int debugIndent = 2;
	std::vector<Path> paths;
    std::vector<Macro> macros;
	ProgressBarHelper* entanglerBar;
	int macrosGenerated = 0;
	bool encounteredErrors = false;

	std::vector<EntanglementOccurance> FindEntanglements(PDDLInstance* instance, bool debugMode);
    EntanglementFinder GetEntanglementFinder(bool debugMode);
    EntanglementEvaluator GetEntanglementEvaluator();
    PDDLInstance GenerateMacros(PDDLInstance* instance, std::vector<EntanglementOccurance>* candidates, bool debugMode);
	
	void PrintEntanglerSteps(std::vector<EntanglementOccurance>* candidates, PDDLInstance* instance);
    void PrintEntanglerDebugData(double ellapsed, std::vector<EntanglementOccurance> *candidates, EntanglementFinder *entanglementFinder, EntanglementEvaluator *entanglementEvaluator);
};

#endif