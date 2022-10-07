#ifndef PDDLCodeGenerator_H
#define PDDLCodeGenerator_H

#include "../PDDLParser/pddldriver.hh"
#include "PDDLDomainCodeGenerator.h"
#include "PDDLProblemCodeGenerator.h"
#include "../PDDLTypes/PDDLInstance.hpp"
#include <string>
#include <fstream>
#include <streambuf>

using namespace std;

class PDDLCodeGenerator {
public:
	void GenerateCode(PDDLInstance document, string domainFile, string problemFile);

private:
	PDDLDomainCodeGenerator domainGenerator;
	PDDLProblemCodeGenerator problemGenerator;
};

#endif