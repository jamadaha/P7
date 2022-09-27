#ifndef CommonInterface_H
#define CommonInterface_H

#include "../Reformulators/BaseReformulator.h"
#include "../PDDLParser/pddldriver.hh"
#include "../PDDLCodeGenerator/PDDLCodeGenerator.h"
#include "../SASCodeGenerator/SASCodeGenerator.h"
#include "../PDDLParser/PDDLDocument.h"
#include <string>
#include <fstream>
#include <streambuf>
#include <vector>
#include <memory>
#include "../Config/config.h"
#include "../DownwardRunner/DownwardRunner.h"

using namespace std;

class CommonInterface {
public:
	CommonInterface(Config config, std::shared_ptr<BaseReformulator> reformulator, string tempDomainName = "tempDomain.pddl", string tempProblemName = "tempProblem.pddl", string fastDownwardSASName = "temp_sas_plan", string outputSASName = "sas_plan") :
	config(config), Reformulator(reformulator), TempDomainName(tempDomainName), TempProblemName(tempProblemName), FastDownwardSASName(fastDownwardSASName), OutputSASName(outputSASName){};

	void Run(string domainFile, string problemFile);

private:
	Config config;
	std::shared_ptr<BaseReformulator> Reformulator;
	string TempDomainName;
	string TempProblemName;
	string FastDownwardSASName;
	string OutputSASName;
	
};

#endif