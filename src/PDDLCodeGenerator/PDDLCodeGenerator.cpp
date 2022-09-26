#include "PDDLCodeGenerator.h"

using namespace std;

void PDDLCodeGenerator::GenerateCode(PDDLDriver* driver, string domainFile, string problemFile) {
	domainGenerator.GenerateDomainFile(driver->domain, domainFile);
	problemGenerator.GenerateProblemFile(driver->problem, problemFile);
}
