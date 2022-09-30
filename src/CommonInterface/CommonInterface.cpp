#include "CommonInterface.h"

void CommonInterface::Run() {
	// Parse original PDDL files
	cout << "Parsing PDDL files" << endl;
	PDDLDriver originalDriver;
	originalDriver.parse(config.domainFile);
	originalDriver.parse(config.problemFile);
	PDDLDocument originalPDDLDocument(originalDriver.domain, originalDriver.problem);

	// Reformulate the PDDL file
	cout << "Reformulating PDDL" << endl;
	PDDLDocument reformulatedDocument = Reformulator->ReformulatePDDL(&originalPDDLDocument);

	// Generate new PDDL files
	cout << "Generating PDDL files" << endl;
	PDDLCodeGenerator pddlGenerator;
	pddlGenerator.GenerateCode(reformulatedDocument, CommonInterface::TempDomainName, CommonInterface::TempProblemName);

	// Throw the new pddl files into Fast Downward
	cout << "Run new PDDL files with Fast Downward" << endl;
	auto runRes = DownwardRunner::RunDownward(config, CommonInterface::TempDomainName, CommonInterface::TempProblemName);
	if (runRes != DownwardRunner::FoundPlan) {
		cout << "No solution could be found for the plan" << endl;
		return;
	}
	else {
		// Parse the output SAS plan
		cout << "Parse SAS Plan" << endl;
		SASParser sasParser;
		SASPlan reformulatedSASPlan = sasParser.Parse(CommonInterface::FastDownwardSASName);

		// Rebuild the SAS Plan
		cout << "Rebuild the SAS plan" << endl;
		SASPlan outputPlan = Reformulator->RebuildSASPlan(&reformulatedSASPlan);

		// Output the new SAS plan
		cout << "Output new SAS Plan" << endl;
		SASCodeGenerator sasGenerator;
		sasGenerator.GenerateCode(outputPlan, CommonInterface::OutputSASName);

		// Validate reformulated plan works with original domain and problem
		cout << "Validate new SAS plan" << endl;
		auto valRes = PlanValidator::ValidatePlan(config, config.domainFile, config.problemFile, CommonInterface::OutputSASName);
		if (valRes != PlanValidator::PlanMatch)
			cout << "Output plan is not valid for original domain and problem!" << endl;
	}
}
