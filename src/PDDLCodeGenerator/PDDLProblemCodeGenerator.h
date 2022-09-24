#ifndef PDDLCodeGenerator_Problem_H
#define PDDLCodeGenerator_Problem_H

#include "../PDDLParser/pddldriver.hh"
#include "BasePDDLCodeGenerator.h"
#include <fstream>

using namespace std;

class PDDLProblemCodeGenerator : public BasePDDLCodeGenerator {
public:
	void GenerateProblemFile(Problem* problem, string problemFile);

private:
	string GetObjects(StringList* objects);
	string GetInits(LiteralList* literals);
	string GetGoals(LiteralList* literals);
};

#endif