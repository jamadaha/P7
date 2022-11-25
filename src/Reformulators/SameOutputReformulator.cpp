#include "SameOutputReformulator.hh"

using namespace std;
using namespace SAS;

PDDLInstance SameOutputReformulator::ReformulatePDDL(PDDLInstance* instance) {
	ConsoleHelper::PrintWarning("Note, this reformulator is only for testing! Simply gives the same result back.", 2);

	PDDLInstance newInstance(instance->domain, instance->problem);

	return newInstance;
}
