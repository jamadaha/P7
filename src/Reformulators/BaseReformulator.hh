#ifndef BaseReformulator_HH
#define BaseReformulator_HH

#include "../IntermediatePDDL/PDDLInstance.hh"
#include "../SAS/Plan.hh"
#include "../Config/Config.hh"
#include "../RunReport/RunReport.hh"

#include "../JointPaths/Finder/Finder.hh"
#include "../JointPaths/JointPath.hh"
#include "../JointPaths/Evaluator/Evaluator.hh"
#include "../JointPaths/Evaluator/EvaluationModifiers.hh"

#include "../MacroGenerator/MacroGenerator.hh"
#include "../MacroGenerator/InstanceGenerator.hh"

#include "../Helpers/ProgressBarHelper.hh"

#include "../MacroVerifyer/MacroVerifyer.hh"
#include "../WalkerPathVerifyer/WalkerPathVerifyer.hh"

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
	std::vector<Path> paths;
    std::vector<Macro> macros;
	ProgressBarHelper* entanglerBar;
	int macrosGenerated = 0;
	bool encounteredErrors = false;

	void ValidatePaths(PDDLInstance *instance, int parentReportID, bool debugMode);
	std::vector<JointPaths::JointPath> FindEntanglements(PDDLInstance* instance, bool debugMode);
    JointPaths::Finder GetEntanglementFinder(bool debugMode);
    JointPaths::Evaluator GetEntanglementEvaluator();
    PDDLInstance GenerateMacros(PDDLInstance* instance, std::vector<JointPaths::JointPath>* candidates, bool debugMode);
	
	void PrintEntanglerSteps(std::vector<JointPaths::JointPath>* candidates, PDDLInstance* instance);
    void PrintEntanglerDebugData(double ellapsed, std::vector<JointPaths::JointPath> *candidates, JointPaths::Finder *entanglementFinder, JointPaths::Evaluator *entanglementEvaluator);
};

#endif