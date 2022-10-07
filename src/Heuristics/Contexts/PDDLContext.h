#ifndef PDDLContext_H
#define PDDLContext_H

#include "BaseContext.h"
#include "../../PDDLTypes/PDDLInstance.hpp"

using namespace std;

class PDDLContext : public BaseContext {
public:
	PDDLDomain* DomainContext;
	PDDLProblem* ProblemContext;
};

#endif