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

using namespace std;

class CommonInterface {
public:
	BaseReformulator* Reformulator;
	string TempDomainName;
	string TempProblemName;
	string FastDownwardSASName;
	string OutputSASName;

	CommonInterface(BaseReformulator* reformulator, string tempDomainName = "tempDomain.pddl", string tempProblemName = "tempProblem.pddl", string fastDownwardSASName = "temp_sas_plan", string outputSASName = "sas_plan") :
	Reformulator(reformulator), TempDomainName(tempDomainName), TempProblemName(tempProblemName), FastDownwardSASName(fastDownwardSASName), OutputSASName(outputSASName){};

	void Run(string domainFile, string problemFile);

private:
	
};

#endif