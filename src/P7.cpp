#include <iostream>
#include "PDDLParser/pddldriver.hh"
#include "SASParser/SASParser.h"
#include "PDDLCodeGenerator/PDDLCodeGenerator.h"
#include "SASCodeGenerator/SASCodeGenerator.h"

using namespace std;

int main()
{
	PDDLDriver driver;
	driver.parse("Data/gripper.pddl");
	driver.parse("Data/gripper-4.pddl");

	PDDLCodeGenerator pddlGenerator;
	pddlGenerator.GenerateAndVerifyCode(&(driver), "Data/gripper.pddl", "Data/newDomain.pddl", "Data/gripper-4.pddl", "Data/newProblem.pddl");


	SASParser parser;
	auto a = parser.Parse("Data/test_sas_plan");

	SASCodeGenerator sasGenerator;
	sasGenerator.GenerateCode(a, "Data/new_sas_plan");

	return 0;
}
