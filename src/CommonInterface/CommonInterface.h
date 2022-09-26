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

using namespace std;

class CommonInterface {
public:
	string TempDomainName = "tempDomain.pddl";
	string TempProblemName = "tempProblem.pddl";
	string FastDownwardSASName = "temp_sas_plan";
	string OutputSASName = "sas_plan";

	void Run(string domainFile, string problemFile);

private:
	BaseReformulator reformulator;
	PDDLDriver originalDriver;
	PDDLDriver reformulatedDriver;
	PDDLCodeGenerator pddlGenerator;
	SASParser sasParser;
	SASCodeGenerator sasGenerator;
};

#endif