#include "SameOutputReformulator.hh"

using namespace std;
using namespace SAS;

PDDL::Instance SameOutputReformulator::ReformulatePDDL(PDDL::Instance* instance) {
	ConsoleHelper::PrintWarning("Note, this reformulator is only for testing! Simply gives the same result back.", 2);

	PDDL::Instance newInstance(instance->domain, instance->problem);

	return newInstance;
}
