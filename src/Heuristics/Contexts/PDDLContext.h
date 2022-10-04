#ifndef PDDLContext_H
#define PDDLContext_H

#include "BaseContext.h"
#include "../../PDDLParser/pddldriver.hh"

using namespace std;

class PDDLContext : public BaseContext {
public:
	Domain* DomainContext;
	Problem* ProblemContext;
};

#endif