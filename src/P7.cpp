#include <iostream>
#include "PDDLParser/pddldriver.hh"
#include "SASParser/SASParser.h"
#include "PDDLCodeGenerator/PDDLCodeGenerator.h"
#include "SASCodeGenerator/SASCodeGenerator.h"

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

	cout << "Parsing SAS file...\n";
	SASParser parser;
	auto a = parser.Parse("Data/test_sas_plan");
	cout << "Done!\n";

	cout << "Generating SAS file...\n";
	SASCodeGenerator sasGenerator;
	sasGenerator.GenerateCode(a, "Data/new_sas_plan");
	cout << "Done!\n";

	return 0;
}
