#include "CommonInterface.h"

#include "../LabDownwardRunner/LabDownwardRunner.h"

void CommonInterface::Run() {
	// Parse original PDDL files
	cout << "Parsing PDDL files...";
	PDDLDriver originalDriver;
	originalDriver.parse(config.domainFile);
	originalDriver.parse(config.problemFile);
	PDDLDocument originalPDDLDocument(originalDriver.domain, originalDriver.problem);
	cout << "   ✓" << endl;

	// Reformulate the PDDL file
	cout << "Reformulating PDDL...";
	PDDLDocument reformulatedDocument = Reformulator->ReformulatePDDL(&originalPDDLDocument);
	cout << "   ✓" << endl;

	// Generate new PDDL files
	cout << "Generating PDDL files...";
	PDDLCodeGenerator pddlGenerator;
	pddlGenerator.GenerateCode(reformulatedDocument, CommonInterface::TempDomainName, CommonInterface::TempProblemName);
	cout << "   ✓" << endl;

	// Throw the new pddl files into Fast Downward
	cout << "Run new PDDL files with Fast Downward...";
	auto runRes = LabDownwardRunner::RunLab(config, CommonInterface::TempDomainName, CommonInterface::TempProblemName);
	if (runRes != DownwardRunner::FoundPlan) {
		cout << "   ✕" << endl;
		cout << "No solution could be found for the plan" << endl;
		return;
	}
	else {
		cout << "   ✓" << endl;

		// Check to make sure the reformulated plan also matches the reformulated problem and domain
		cout << "Validate reformulated SAS plan...";
		auto reformulatedSASValidatorResult = PlanValidator::ValidatePlan(config, CommonInterface::TempDomainName, CommonInterface::TempProblemName, CommonInterface::FastDownwardSASName);
		if (reformulatedSASValidatorResult != PlanValidator::PlanMatch) {
			cout << "   ✕" << endl;
			cout << "Output plan is not valid for reformulated domain and problem!" << endl;
			return;
		}
		cout << "   ✓" << endl;

		// Parse the output SAS plan
		cout << "Parse SAS Plan...";
		SASParser sasParser;
		filesystem::path sasPath = filesystem::path(CommonInterface::FastDownwardSASName);
		SASPlan reformulatedSASPlan = sasParser.Parse(sasPath);
		cout << "   ✓" << endl;

		// Rebuild the SAS Plan
		cout << "Rebuild the SAS plan...";
		SASPlan outputPlan = Reformulator->RebuildSASPlan(&reformulatedSASPlan);
		cout << "   ✓" << endl;

		// Output the new SAS plan
		cout << "Output new SAS Plan...";
		SASCodeGenerator sasGenerator;
		sasGenerator.GenerateCode(outputPlan, CommonInterface::OutputSASName);
		cout << "   ✓" << endl;

		// Validate reformulated plan works with original domain and problem
		cout << "Validate new SAS plan...";
		auto newSASValidatorResult = PlanValidator::ValidatePlan(config, config.domainFile, config.problemFile, CommonInterface::OutputSASName);
		if (newSASValidatorResult != PlanValidator::PlanMatch) {
			cout << "   ✕" << endl;
			cout << "Output plan is not valid for original domain and problem!" << endl;
			return;
		}
		cout << "   ✓" << endl;
	}
}
