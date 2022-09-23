#ifndef PDDLCodeGenerator_H
#define PDDLCodeGenerator_H

#include "../PDDLParser/pddldriver.hh"
#include <fstream>

using namespace std;

class PDDLCodeGenerator {
public:
	void GenerateCode(PDDLDriver driver, string domainFile, string problemFile);

private:
	void GenerateDomainFile(Domain* domain, string domainFile);
	string GetRequirements(Domain* domain);
	string GetPredicates(Domain* domain);
	string GetArguments(StringList* list);

	void GenerateProblemFile(Problem* problem, string problemFile);
};

#endif