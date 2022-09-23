#include <iostream>
#include "PDDLParser/pddldriver.hh"

using namespace std;

int main()
{
	PDDLDriver driver;
	driver.parse("Data/gripper.pddl");
	driver.parse("Data/gripper-4.pddl");
	cout << *(driver.domain) << endl;
	cout << *(driver.problem) << endl;
	return 0;
}
