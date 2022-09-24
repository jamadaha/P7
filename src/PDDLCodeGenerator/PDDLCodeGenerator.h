#ifndef PDDLCodeGenerator_H
#define PDDLCodeGenerator_H

#include "../PDDLParser/pddldriver.hh"
#include "PDDLDomainCodeGenerator.h"
#include "PDDLProblemCodeGenerator.h"
#include <string>
#include <fstream>
#include <streambuf>

using namespace std;

class PDDLCodeGenerator {
public:
	void GenerateCode(PDDLDriver* driver, string domainFile, string problemFile);
	void GenerateAndVerifyCode(PDDLDriver* driver, string sourceDomainFile, string targetDomainFile, string sourceProblemFile, string targetProblemFile);
	bool VerifyCodeGeneration(string sourceFile, string generatedFile);

private:
	PDDLDomainCodeGenerator domainGenerator;
	PDDLProblemCodeGenerator problemGenerator;

	void RemoveCharacter(string* buffer, char character);
};

#endif