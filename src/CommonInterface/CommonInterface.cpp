#include "CommonInterface.h"
#include "../PDDLParser/PDDLDocument.h"

void CommonInterface::Run(string domainFile, string problemFile) {
	// Parse original PDDL files
	PDDLDriver originalDriver;
	originalDriver.parse(domainFile);
	originalDriver.parse(problemFile);
	PDDLDocument originalPDDLDocument(originalDriver.domain, originalDriver.problem);

	// Reformulate the PDDL file
	PDDLDocument reformulatedDocument = Reformulator->ReformulatePDDL(&originalPDDLDocument);

	// Generate new PDDL files
	PDDLCodeGenerator pddlGenerator;
	pddlGenerator.GenerateCode(reformulatedDocument, CommonInterface::TempDomainName, CommonInterface::TempProblemName);

	// Throw the new pddl files into Fast Downward
	// ...

	// Parse the output SAS plan
	SASParser sasParser;
	Plan reformulatedSASPlan = sasParser.Parse(CommonInterface::FastDownwardSASName);

	// Rebuild the SAS Plan
	Plan outputPlan = Reformulator->RebuildSASPlan(&reformulatedSASPlan);

	// Output the new SAS plan
	SASCodeGenerator sasGenerator;
	sasGenerator.GenerateCode(outputPlan, CommonInterface::OutputSASName);
}
