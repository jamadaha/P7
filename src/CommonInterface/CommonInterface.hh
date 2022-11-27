#ifndef CommonInterface_HH
#define CommonInterface_HH

#include <string>

#include "../RunReport/RunReport.hh"
#include "../PathCheckers/PathChecker.hh"
#include "../Reformulators/BaseReformulator.hh"
#include "../Reformulators/SameOutputReformulator.hh"
#include "../Reformulators/Walkers/GreedyWalkerReformulator.hh"
#include "../Reformulators/Walkers/GreedyResumeWalkerReformulator.hh"
#include "../Reformulators/Walkers/QueueWalkerReformulator.hh"
#include "../Reformulators/Regressors/PartialRegressionReformulator.hh"
#include "../Reformulators/Regressors/RegressionReformulator.hh"
#include "../Reformulators/Walkers/ProbeWalkerReformulator.hh"
#include "../Reformulators/Walkers/StepBackWalkerReformulator.hh"
#include "../PDDL/CodeGenerators/CodeGenerator.hh"
#include "../SAS/CodeGenerator/CodeGenerator.hh"
#include "../SAS/Parser/Parser.hh"
#include "../Config/Config.hh"
#include "../DownwardRunner/DownwardRunner.hh"
#include "../PlanValidators/PlanValidator.hh"
#include "../PDDL/Instance.hh"
#include "../PDDL/Mutex.hh"
#include "../Helpers/ConsoleHelper.hh"
#include "../PDDL/Parsers/ExternalParser.hh"

template <class T>
struct InterfaceStep {
	bool RanWithoutErrors;
	T Data;

	InterfaceStep(T data, bool ranWithoutErrors = true) : Data(data), RanWithoutErrors(ranWithoutErrors) {};
};
template <>
struct InterfaceStep<void> {
	bool RanWithoutErrors;

	InterfaceStep(bool ranWithoutErrors = true) : RanWithoutErrors(ranWithoutErrors) {};
};

class CommonInterface {
public:
	enum RunResult { None, RanWithoutErrors, ErrorsEncountered };
	CommonInterface(Config config, RunReport* report, bool isDirect, std::string tempDomainName = "tempDomain.pddl", std::string tempProblemName = "tempProblem.pddl", std::string fastDownwardSASName = "sas_plan", std::string outputSASName = "real_sas_plan") :
	config(config), Report(report), isDirect(isDirect), TempDomainName(tempDomainName), TempProblemName(tempProblemName), FastDownwardSASName(fastDownwardSASName), OutputSASName(outputSASName) {};

	enum RunResult Run(int reformulatorIndex = 0);

private:
	enum ReformulatorRunResultResult { _None, ReformulatorFailed, FoundPlan, DidNotFindPlan };
	InterfaceStep<BaseReformulator*> GetReformulator(int reformulatorIndex = 0);
	InterfaceStep<void> CheckFilePaths();
	InterfaceStep<PDDL::Instance*> ParsePDDLFiles();
	InterfaceStep<void> RunIteratively(BaseReformulator* reformulator, PDDL::Instance* instance);
	InterfaceStep<void> RunDirect(BaseReformulator* reformulator, PDDL::Instance* instance);
	InterfaceStep<ReformulatorRunResultResult> RunSingle(BaseReformulator* reformulator, PDDL::Instance* instance, int reportID, int reformulatorTimeLimit, int downwardTimeLimit);
	InterfaceStep<void> ValidatePlans(std::string domainFile, std::string problemFile, std::string sasFile, std::string reportName);
	InterfaceStep<SAS::Plan> ParseSASPlan();
	InterfaceStep<SAS::Plan> RebuildSASPlan(SAS::Plan* reformulatedSASPlan, BaseReformulator* reformulator, PDDL::Instance* instance);
	InterfaceStep<void> GenerateNewSASPlan(SAS::Plan outputPlan);

	RunReport* Report;
	Config config;
	std::string TempDomainName;
	std::string TempProblemName;
	std::string FastDownwardSASName;
	std::string OutputSASName;
	bool isDirect = false;
};

#endif
