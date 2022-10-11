#ifndef BaseReformulator_H
#define BaseReformulator_H

#include "../PDDLTypes/PDDLInstance.hpp"
#include "../SASParser/SASParser.h"

class BaseReformulator {
public:
	virtual PDDLInstance ReformulatePDDL(PDDLInstance* instance) = 0;
	virtual SASPlan RebuildSASPlan(SASPlan* reformulatedSAS) = 0;
};

#endif