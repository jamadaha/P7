#include "CommonInterface.h"
#include "../PDDLParser/PDDLDocument.h"

void CommonInterface::Run() {
	// Parse original PDDL files
	PDDLDriver originalDriver;
	originalDriver.parse(config.domainFile);
	originalDriver.parse(config.problemFile);
	PDDLDocument originalPDDLDocument(originalDriver.domain, originalDriver.problem);

	// Reformulate the PDDL file
	PDDLDocument reformulatedDocument = Reformulator->ReformulatePDDL(&originalPDDLDocument);

	// Generate new PDDL files
	PDDLCodeGenerator pddlGenerator;
	pddlGenerator.GenerateCode(reformulatedDocument, CommonInterface::TempDomainName, CommonInterface::TempProblemName);

	// Throw the new pddl files into Fast Downward
	DownwardRunner::runDownward(config, CommonInterface::TempDomainName, CommonInterface::TempProblemName);

	// Parse the output SAS plan
	SASParser sasParser;
	SASPlan reformulatedSASPlan = sasParser.Parse(CommonInterface::FastDownwardSASName);

	// Rebuild the SAS Plan
	SASPlan outputPlan = Reformulator->RebuildSASPlan(&reformulatedSASPlan);

	// Output the new SAS plan
	SASCodeGenerator sasGenerator;
	sasGenerator.GenerateCode(outputPlan, CommonInterface::OutputSASName);
}
