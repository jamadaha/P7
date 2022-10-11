#ifndef BaseReformulator_HH
#define BaseReformulator_HH

#include "../PDDLTypes/PDDLInstance.hpp"
#include "../SASParser/SASParser.hh"

class BaseReformulator {
public:
	virtual PDDLInstance ReformulatePDDL(PDDLInstance* instance) = 0;
	virtual SASPlan RebuildSASPlan(SASPlan* reformulatedSAS) = 0;
};

#endif