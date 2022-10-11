#ifndef PDDLContext_HH
#define PDDLContext_HH

#include "BaseContext.h"
#include "../../PDDLTypes/PDDLInstance.hpp"

class PDDLContext : public BaseContext {
public:
	PDDLDomain* DomainContext;
	PDDLProblem* ProblemContext;
};

#endif