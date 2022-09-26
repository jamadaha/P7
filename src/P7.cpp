#include <iostream>
#include "PDDLParser/pddldriver.hh"
#include "SASParser/SASParser.h"
#include "PDDLCodeGenerator/PDDLCodeGenerator.h"
#include "SASCodeGenerator/SASCodeGenerator.h"
#include "FileVerifier/FileVerifier.h"

using namespace std;

int main()
{
	cout << "Parsing PDDL files...\n";
	PDDLDriver driver;
	driver.parse("Data/gripper.pddl");
	driver.parse("Data/gripper-4.pddl");
	cout << "Done!\n";

	cout << "Generating PDDL files...\n";
	PDDLCodeGenerator pddlGenerator;
	pddlGenerator.GenerateAndVerifyCode(&(driver), "Data/gripper.pddl", "Data/newDomain.pddl", "Data/gripper-4.pddl", "Data/newProblem.pddl");
	cout << "Done!\n";

	PDDLCodeGenerator generator;
	generator.GenerateCode(&(driver), "Data/newDomain.pddl", "Data/newProblem.pddl");

	FileVerifier verifier;
	if (!verifier.VerifyFiles("Data/gripper.pddl", "Data/newDomain.pddl"))
		throw invalid_argument("Files not the same!");
	if (!verifier.VerifyFiles("Data/gripper-4.pddl", "Data/newProblem.pddl"))
		throw invalid_argument("Files not the same!");

	return 0;
}
