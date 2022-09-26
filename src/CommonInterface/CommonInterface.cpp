#include "CommonInterface.h"

void CommonInterface::Run(string domainFile, string problemFile) {
	// Parse original PDDL files
	originalDriver.parse(domainFile);
	originalDriver.parse(problemFile);

	// Reformulate the PDDL file
	CommonInterface::reformulatedDriver = *(reformulator.ReformulatePDDL(&(originalDriver)));

	// Generate new PDDL files
	pddlGenerator.GenerateCode(&reformulatedDriver, CommonInterface::TempDomainName, CommonInterface::TempProblemName);

	// Throw the new pddl files into Fast Downward
	// ...

	// Parse the output SAS plan
	sasParser.Parse(CommonInterface::FastDownwardSASName);

	// Rebuild the SAS Plan
	Plan* outputPlan = reformulator.RebuildSASPlan(sasParser.SASPlan);

	// Output the new SAS plan
	sasGenerator.GenerateCode(outputPlan, CommonInterface::OutputSASName);
}
