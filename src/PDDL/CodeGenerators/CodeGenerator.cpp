#include "PDDLCodeGenerator.hh"

using namespace std;

void PDDLCodeGenerator::GenerateCode(PDDLInstance document, string domainFile, string problemFile) {
	domainGenerator.GenerateDomainFile(domainFile);
	problemGenerator.GenerateProblemFile(problemFile);
}
