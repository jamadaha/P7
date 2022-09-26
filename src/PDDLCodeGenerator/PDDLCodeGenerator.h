#ifndef PDDLCodeGenerator_H
#define PDDLCodeGenerator_H

#include "../PDDLParser/pddldriver.hh"
#include "PDDLDomainCodeGenerator.h"
#include "PDDLProblemCodeGenerator.h"
#include "../PDDLParser/PDDLDocument.h"
#include <string>
#include <fstream>
#include <streambuf>

using namespace std;

class PDDLCodeGenerator {
public:
	void GenerateCode(PDDLDocument document, string domainFile, string problemFile);

private:
	PDDLDomainCodeGenerator domainGenerator;
	PDDLProblemCodeGenerator problemGenerator;
};

#endif