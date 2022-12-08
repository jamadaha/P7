#ifndef BaseReformulator_HH
#define BaseReformulator_HH

#include "../PDDL/Instance.hh"

#include "../SAS/Plan.hh"
#include "../SAS/CodeGenerator/CodeGenerator.hh"
#include "../SAS/Parser/Parser.hh"
#include "../SAS/Rebuilder/Rebuilder.hh"
#include "../Config/Config.hh"
#include "../RunReport/RunReport.hh"

#include "../JointPaths/Finder/Finder.hh"
#include "../JointPaths/JointPath.hh"
#include "../JointPaths/Evaluator/Evaluator.hh"
#include "../JointPaths/Evaluator/EvaluationModifiers.hh"

#include "../Macros/Generators/Generator.hh"
#include "../Macros/Instantiators/Instantiator.hh"

#include "../Helpers/ProgressBarHelper.hh"

#include "../WalkerPathVerifyer/WalkerPathVerifyer.hh"

class BaseReformulator {
public:
	int TimeLimit = 1000;
	int Iteration = 1;
	int ReportID = -1;
	int GetMacrosGenerated() { return macrosGenerated; };
	int GetActionsGenerated() { return actionsGenerated; };
	int GetActionIterationGenerated() { return actionIterationGenerated; };
	int GetInvalidActionIterationGenerated() { return invalidActionIterationGenerated; };
	std::vector<unsigned int> GetBranchingFactors() { return branchingFactors; };
	std::vector<unsigned int> GetPathLengths() { return pathLengths; };
	bool DidEncounterErrors() { return encounteredErrors; };
	unsigned int GetTotalWalkingTime() { return _totalWalkingTime; };
	unsigned int GetTotalWalkSteps() { return _totalWalkSteps; };

	BaseReformulator(Config* config, RunReport* report) : Configs(config), Report(report) {

	}

	virtual PDDL::Instance ReformulatePDDL(PDDL::Instance* instance) = 0;
	SAS::Plan RebuildSASPlan(PDDL::Instance* instance, SAS::Plan* reformulatedSAS);
protected:
	Config* Configs;
	RunReport* Report;
	const int debugIndent = 2;
	std::vector<Path> paths;
    std::vector<Macros::Macro> macros;
	ProgressBarHelper* entanglerBar;
	int macrosGenerated = 0;
	int actionsGenerated = 0;
	int actionIterationGenerated = 0;
	int invalidActionIterationGenerated = 0;
	unsigned int _totalWalkingTime = 0;
	unsigned int _totalWalkSteps = 0;
	bool encounteredErrors = false;
	std::vector<unsigned int> branchingFactors;
	std::vector<unsigned int> pathLengths;

	void ValidatePaths(PDDL::Instance *instance, int parentReportID, bool debugMode);
	std::vector<JointPaths::JointPath> FindEntanglements(PDDL::Instance* instance, bool debugMode);
    JointPaths::Finder GetEntanglementFinder(bool debugMode);
    JointPaths::Evaluator GetEntanglementEvaluator();
    PDDL::Instance GenerateMacros(PDDL::Instance* instance, std::vector<JointPaths::JointPath>* candidates, bool debugMode);
	
	void PrintEntanglerSteps(std::vector<JointPaths::JointPath>* candidates, PDDL::Instance* instance);
    void PrintEntanglerDebugData(double ellapsed, std::vector<JointPaths::JointPath> *candidates, JointPaths::Finder *entanglementFinder, JointPaths::Evaluator *entanglementEvaluator);
};

#endif