#ifndef CommonInterface_H
#define CommonInterface_H

#include <string>

#include "../RunReport/RunReport.hh"
#include "../PathCheckers/PathChecker.hh"
#include "../Reformulators/BaseReformulator.hh"
#include "../PDDLParser/pddldriver.hh"
#include "../PDDLCodeGenerator/PDDLCodeGenerator.hh"
#include "../SASCodeGenerator/SASCodeGenerator.hh"
#include "../SASParser/SASParser.hh"
#include "../Config/config.h"
#include "../DownwardRunner/DownwardRunner.hh"
#include "../PlanValidators/PlanValidator.hh"
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
	CommonInterface(Config config, std::shared_ptr<BaseReformulator> reformulator, std::string tempDomainName = "tempDomain.pddl", std::string tempProblemName = "tempProblem.pddl", std::string fastDownwardSASName = "sas_plan", std::string outputSASName = "real_sas_plan") :
	config(config), Reformulator(reformulator), TempDomainName(tempDomainName), TempProblemName(tempProblemName), FastDownwardSASName(fastDownwardSASName), OutputSASName(outputSASName){};

	enum RunResult Run(RunReport* report);

private:
	Config config;
	std::shared_ptr<BaseReformulator> Reformulator;
	std::string TempDomainName;
	std::string TempProblemName;
	std::string FastDownwardSASName;
	std::string OutputSASName;
	
};

#endif
