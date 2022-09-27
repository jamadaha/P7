#ifndef SameOutputReformulator_H
#define SameOutputReformulator_H

using namespace std;

#include "BaseReformulator.h"

class SameOutputReformulator : public BaseReformulator {
	PDDLDocument ReformulatePDDL(PDDLDocument* inputPDDL) override;
	Plan RebuildSASPlan(Plan* reformulatedSAS) override;
};

#endif