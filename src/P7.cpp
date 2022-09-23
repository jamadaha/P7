#include <iostream>
#include "PDDLParser/pddldriver.hh"
#include "SASParser/SASParser.h"

using namespace std;

int main()
{
	SASParser parser;
	auto a = parser.Parse("Data/test_sas_plan");

	PDDLDriver driver;
	driver.parse("Data/gripper.pddl");
	driver.parse("Data/gripper-4.pddl");
	cout << *(driver.domain) << endl;
	cout << *(driver.problem) << endl;
	return 0;
}
