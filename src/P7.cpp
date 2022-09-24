#include <iostream>
#include "PDDLParser/pddldriver.hh"
#include "SASParser/SASParser.h"
#include "PDDLCodeGenerator/PDDLCodeGenerator.h"

using namespace std;

int main()
{
	//SAS_Parser parser;
	//auto a = parser.Parse("Data/test_sas_plan");

	PDDLDriver driver;
	driver.parse("Data/gripper.pddl");
	driver.parse("Data/gripper-4.pddl");

	PDDLCodeGenerator generator;
	generator.GenerateAndVerifyCode(&(driver), "Data/gripper.pddl", "Data/newDomain.pddl", "Data/gripper-4.pddl", "Data/newProblem.pddl");

	return 0;
}
