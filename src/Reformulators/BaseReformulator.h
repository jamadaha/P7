#ifndef BaseReformulator_H
#define BaseReformulator_H

#include "../PDDLParser/pddldriver.hh"
#include "../SASParser/SASParser.h"
#include <string>
#include <fstream>
#include <streambuf>

using namespace std;

class BaseReformulator {
public:
	PDDLDriver* ReformulatePDDL(PDDLDriver* inputPDDL);
	Plan* RebuildSASPlan(Plan* reformulatedSAS);
};

#endif