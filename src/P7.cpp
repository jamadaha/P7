#include <iostream>
#include "PDDLParser/pddldriver.hh"
#include "SASParser/SASParser.h"
#include "PDDLCodeGenerator/PDDLCodeGenerator.h"
#include "SASCodeGenerator/SASCodeGenerator.h"
#include "FileVerifier/FileVerifier.h"

using namespace std;

int main()
{
	FileVerifier verifier;

	cout << "Parsing PDDL files...\n";
	PDDLDriver driver;
	driver.parse("Data/gripper.pddl");
	driver.parse("Data/gripper-4.pddl");
	cout << "Done!\n";

	cout << "Generating PDDL files...\n";
	PDDLCodeGenerator pddlGenerator;
	pddlGenerator.GenerateCode(&(driver), "Data/newDomain.pddl", "Data/newProblem.pddl");
	cout << "Done!\n";

	cout << "Verifying PDDL files...\n";
	if (!verifier.VerifyFiles("Data/gripper.pddl", "Data/newDomain.pddl"))
		throw invalid_argument("Files not the same!");
	if (!verifier.VerifyFiles("Data/gripper-4.pddl", "Data/newProblem.pddl"))
		throw invalid_argument("Files not the same!");
	cout << "Done!\n";

	cout << "Parsing SAS file...\n";
	SASParser sasParser;
	Plan sasPlan = sasParser.Parse("Data/test_sas_plan");
	cout << "Done!\n";

	cout << "Generating SAS file...\n";
	SASCodeGenerator sasGenerator;
	sasGenerator.GenerateCode(sasPlan, "Data/new_sas_plan");
	cout << "Done!\n";

	cout << "Verifying SAS file...\n";
	if (!verifier.VerifyFiles("Data/test_sas_plan", "Data/new_sas_plan"))
		throw invalid_argument("Files not the same!");
	cout << "Done!\n";

	return 0;
}
