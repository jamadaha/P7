#include <iostream>
#include "PDDLParser/pddldriver.hh"
#include "SASParser/SASParser.h"
#include "PDDLCodeGenerator/PDDLCodeGenerator.h"
#include "FileVerifier/FileVerifier.h"

using namespace std;

int main()
{
	SASParser parser;
	auto a = parser.Parse("Data/test_sas_plan");

	PDDLDriver driver;
	driver.parse("Data/gripper.pddl");
	driver.parse("Data/gripper-4.pddl");

	PDDLCodeGenerator generator;
	generator.GenerateCode(&(driver), "Data/newDomain.pddl", "Data/newProblem.pddl");

	FileVerifier verifier;
	if (!verifier.VerifyFiles("Data/gripper.pddl", "Data/newDomain.pddl"))
		throw invalid_argument("Files not the same!");
	if (!verifier.VerifyFiles("Data/gripper-4.pddl", "Data/newProblem.pddl"))
		throw invalid_argument("Files not the same!");

	return 0;
}
