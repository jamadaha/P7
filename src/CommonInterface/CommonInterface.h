#ifndef CommonInterface_H
#define CommonInterface_H

#include <string>

#include "../RunReport/RunReport.hh"
#include "../PathCheckers/PathChecker.hh"
#include "../Reformulators/BaseReformulator.hh"
#include "../PDDLParser/pddldriver.hh"
#include "../PDDLCodeGenerator/PDDLCodeGenerator.h"
#include "../SASCodeGenerator/SASCodeGenerator.hh"
#include "../SASParser/SASParser.h"
#include "../Config/config.h"
#include "../DownwardRunner/DownwardRunner.h"
#include "../PlanValidators/PlanValidator.h"
#include "../PDDLTypes/PDDLDomain.hpp"
#include "../PDDLTypes/PDDLProblem.hpp"
#include "../PDDLTypes/PDDLInstance.hpp"

// Note: If include of actiongenerator still exists here remove it
// it was added for temp reasons
#include "../Entangler/ActionGenerator.hpp"
#include "../PDDLTypes/PDDLActionInstance.hpp"

class CommonInterface {
public:
	enum RunResult { None, RanWithoutErrors, ErrorsEncountered };
	CommonInterface(Config config, std::shared_ptr<BaseReformulator> reformulator, string tempDomainName = "tempDomain.pddl", string tempProblemName = "tempProblem.pddl", string fastDownwardSASName = "sas_plan", string outputSASName = "real_sas_plan") :
	config(config), Reformulator(reformulator), TempDomainName(tempDomainName), TempProblemName(tempProblemName), FastDownwardSASName(fastDownwardSASName), OutputSASName(outputSASName){};

	enum RunResult Run(RunReport* report);

private:
	Config config;
	std::shared_ptr<BaseReformulator> Reformulator;
	string TempDomainName;
	string TempProblemName;
	string FastDownwardSASName;
	string OutputSASName;
	
};

#endif
