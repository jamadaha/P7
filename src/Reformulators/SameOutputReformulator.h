#ifndef SameOutputReformulator_H
#define SameOutputReformulator_H

using namespace std;

#include "BaseReformulator.h"

class SameOutputReformulator : public BaseReformulator {
	PDDLDocument ReformulatePDDL(PDDLDocument* inputPDDL) override;
	SASPlan RebuildSASPlan(SASPlan* reformulatedSAS) override;
};

#endif