#ifndef BaseReformulator_H
#define BaseReformulator_H

#include "../PDDLParser/pddldriver.hh"
#include "../PDDLParser/PDDLDocument.h"
#include "../SASParser/SASParser.h"
#include <string>
#include <fstream>
#include <streambuf>

using namespace std;

class BaseReformulator {
public:
	PDDLDocument ReformulatePDDL(PDDLDocument* inputPDDL);
	Plan RebuildSASPlan(Plan* reformulatedSAS);
};

#endif