#include <iostream>
#include "PDDLParser/pddldriver.hh"
#include "SASParser/SASParser.h"
#include "PDDLCodeGenerator/PDDLCodeGenerator.h"
#include "Config/config.h"
#include "DownwardRunner/DownwardRunner.h"
#include "SASCodeGenerator/SASCodeGenerator.h"
#include "FileVerifier/FileVerifier.h"
#include "CommonInterface/CommonInterface.h"
#include "Reformulators/SameOutputReformulator.h"

using namespace std;

int main(int argc, char** argv)
{
	cout << "Running reformulator..." << endl;
	BaseReformulator* reformulator = new SameOutputReformulator();
	CommonInterface interface = CommonInterface(reformulator, "Data/newDomain.pddl", "Data/newProblem.pddl", "Data/test_sas_plan", "Data/new_sas_plan");
	interface.Run("Data/gripper.pddl", "Data/gripper-4.pddl");
	cout << "Done!" << endl;

	FileVerifier verifier;
	cout << "Verifying PDDL files..." << endl;
	if (!verifier.VerifyFiles("Data/gripper.pddl", "Data/newDomain.pddl"))
		throw invalid_argument("Files not the same!");
	if (!verifier.VerifyFiles("Data/gripper-4.pddl", "Data/newProblem.pddl"))
		throw invalid_argument("Files not the same!");
	cout << "Done!" << endl;

	Config c = Config::parseArgs(argc, argv);
	DownwardRunner::runDownward(c);

	cout << "Verifying SAS file..." << endl;
	if (!verifier.VerifyFiles("Data/test_sas_plan", "Data/new_sas_plan"))
		throw invalid_argument("Files not the same!");
	cout << "Done!" << endl;

	return 0;
}
