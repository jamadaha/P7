#include <iostream>
#include <memory>
#include "PDDLParser/pddldriver.hh"
#include "SASParser/SASParser.h"
#include "PDDLCodeGenerator/PDDLCodeGenerator.h"
#include "Config/config.h"
#include "SASCodeGenerator/SASCodeGenerator.h"
#include "FileVerifier/FileVerifier.h"
#include "CommonInterface/CommonInterface.h"
#include "Reformulators/SameOutputReformulator.h"

#include "Report.hh"

using namespace std;

int main(int argc, char** argv)
{
	Config config;
	// Do first as it quits on help
	if (config.parseArgs(&config, argc, argv))
		return 0;

	Report report = Report();

	cout << "Running reformulator..." << endl;	
	std::shared_ptr<BaseReformulator> reformulator = std::make_shared<SameOutputReformulator>();
	CommonInterface interface = CommonInterface(config, reformulator);
	interface.Run(&report);
	cout << "Done!" << endl;

	//FileVerifier verifier;
	//cout << "Verifying PDDL files..." << endl;
	//if (!verifier.VerifyFiles("Data/gripper.pddl", "Data/newDomain.pddl"))
	//	throw invalid_argument("Files not the same!");
	//if (!verifier.VerifyFiles("Data/gripper-4.pddl", "Data/newProblem.pddl"))
	//	throw invalid_argument("Files not the same!");
	//cout << "Done!" << endl;

	//cout << "Verifying SAS file..." << endl;
	//if (!verifier.VerifyFiles("Data/test_sas_plan", "Data/new_sas_plan"))
	//	throw invalid_argument("Files not the same!");
	//cout << "Done!" << endl;

	report.Print();
	return 0;
}
