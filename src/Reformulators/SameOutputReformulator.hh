#ifndef SameOutputReformulator_H
#define SameOutputReformulator_H

#include "BaseReformulator.h"

class SameOutputReformulator : public BaseReformulator {
	PDDLInstance ReformulatePDDL(PDDLInstance* instance) override;
	SASPlan RebuildSASPlan(SASPlan* reformulatedSAS) override;
};

#endif