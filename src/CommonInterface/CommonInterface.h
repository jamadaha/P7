#ifndef CommonInterface_H
#define CommonInterface_H

#include "../Reformulators/BaseReformulator.h"
#include "../PDDLParser/pddldriver.hh"
#include "../PDDLCodeGenerator/PDDLCodeGenerator.h"
#include "../SASCodeGenerator/SASCodeGenerator.h"
#include <string>
#include <fstream>
#include <streambuf>
#include <vector>
#include <memory>
#include "../Config/config.h"
#include "../DownwardRunner/DownwardRunner.h"
#include "../PlanValidators/PlanValidator.h"
#include "../Report.hh"
#include "../PDDLTypes/PDDLDomain.hpp"
#include "../PDDLTypes/PDDLProblem.hpp"
#include "../PDDLTypes/PDDLInstance.hpp"

using namespace std;

class CommonInterface {
public:
	CommonInterface(Config config, std::shared_ptr<BaseReformulator> reformulator, string tempDomainName = "tempDomain.pddl", string tempProblemName = "tempProblem.pddl", string fastDownwardSASName = "sas_plan", string outputSASName = "real_sas_plan") :
	config(config), Reformulator(reformulator), TempDomainName(tempDomainName), TempProblemName(tempProblemName), FastDownwardSASName(fastDownwardSASName), OutputSASName(outputSASName){};

	void Run(Report* report);

private:
	Config config;
	std::shared_ptr<BaseReformulator> Reformulator;
	string TempDomainName;
	string TempProblemName;
	string FastDownwardSASName;
	string OutputSASName;
	
};

#endif
