#ifndef CommonInterface_H
#define CommonInterface_H

#include "../PathCheckers/PathChecker.hh"
#include "../Reformulators/BaseReformulator.h"
#include "../PDDLParser/pddldriver.hh"
#include "../PDDLCodeGenerator/PDDLCodeGenerator.h"
#include "../SASCodeGenerator/SASCodeGenerator.h"
#include "../Config/config.h"
#include "../DownwardRunner/DownwardRunner.h"
#include "../PlanValidators/PlanValidator.h"
#include "../Report.hh"
#include "../PDDLTypes/PDDLDomain.hpp"
#include "../PDDLTypes/PDDLProblem.hpp"
#include "../PDDLTypes/PDDLInstance.hpp"

// Note: If include of actiongenerator still exists here remove it
// it was added for temp reasons
#include "../Walker/Walker.hpp"
#include "../Walker/Heuristics/RandomHeuristic.hh"
#include "../Walker/DepthFunctions/ConstantDepthFunction.h"


using namespace std;

class CommonInterface {
public:
	enum RunResult { None, RanWithoutErrors, ErrorsEncountered };
	CommonInterface(Config config, std::shared_ptr<BaseReformulator> reformulator, string tempDomainName = "tempDomain.pddl", string tempProblemName = "tempProblem.pddl", string fastDownwardSASName = "sas_plan", string outputSASName = "real_sas_plan") :
	config(config), Reformulator(reformulator), TempDomainName(tempDomainName), TempProblemName(tempProblemName), FastDownwardSASName(fastDownwardSASName), OutputSASName(outputSASName){};

	enum RunResult Run(Report* report);

private:
	Config config;
	std::shared_ptr<BaseReformulator> Reformulator;
	string TempDomainName;
	string TempProblemName;
	string FastDownwardSASName;
	string OutputSASName;
	
};

#endif
