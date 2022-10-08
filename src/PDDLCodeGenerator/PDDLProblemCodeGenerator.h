#ifndef PDDLCodeGenerator_Problem_H
#define PDDLCodeGenerator_Problem_H

#include "BasePDDLCodeGenerator.h"
#include <fstream>

using namespace std;

class PDDLProblemCodeGenerator : public BasePDDLCodeGenerator {
public:
	void GenerateProblemFile(PDDLProblem* problem, string problemFile);
	string GenerateProblemString(PDDLProblem* problem);

private:
	string GetObjects(vector<string> objects);
	string GetInits(PDDLState literals);
	string GetGoals(PDDLState literals);
};

#endif