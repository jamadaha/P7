#include "CodeGenerator.hh"

using namespace std;
using namespace PDDL;

void CodeGenerator::GenerateCode(Instance document, string domainFile, string problemFile) {
	domainGenerator.GenerateDomainFile(domainFile);
	problemGenerator.GenerateProblemFile(problemFile);
}
