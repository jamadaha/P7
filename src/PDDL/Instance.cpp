#include "Instance.hh"

#ifndef NDEBUG
using namespace PDDL;

Instance* PDDL::CurrentInstance;

void Instance::SetupDebug() {
	PDDL::CurrentInstance = new Instance(this->domain, this->problem, this->mutexes);
}
#endif
