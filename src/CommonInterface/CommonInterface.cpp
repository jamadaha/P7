#include "CommonInterface.h"

void CommonInterface::Run(Report* report) {
	int64_t t;
	// Parse original PDDL files
	cout << "Parsing PDDL files...";
	report->Begin("Parsing PDDL");
	PDDLDriver originalDriver;
	originalDriver.parse(config.domainFile);
	originalDriver.parse(config.problemFile);
	t = report->Stop();
	cout << "   ✓ " << t << "ms" << endl;

	// Convert PDDL format
	cout << "Converting PDDL format...";
	report->Begin("Converison of PDDL format");
	PDDLDomain domain = PDDLDomain(originalDriver.domain);
	PDDLProblem problem = PDDLProblem(originalDriver.problem, &domain);
	PDDLInstance instance = PDDLInstance(&domain, &problem);
	t = report->Stop();
	cout << "   ✓ " << t << "ms" << endl;

	// Reformulate the PDDL file
	cout << "Reformulating PDDL...";
	report->Begin("Reformulation of PDDL");
	PDDLInstance reformulatedInstance = Reformulator->ReformulatePDDL(&instance);
	t = report->Stop();
	cout << "   ✓ " << t << "ms" << endl;

	// Generate new PDDL files
	cout << "Generating PDDL files...";
	report->Begin("Generating PDDL");
	PDDLCodeGenerator pddlGenerator;
	pddlGenerator.GenerateCode(reformulatedInstance, CommonInterface::TempDomainName, CommonInterface::TempProblemName);
	report->Stop();
	cout << "   ✓ " << t << "ms" << endl;

	// Throw the new pddl files into Fast Downward
	cout << "Run new PDDL files with Fast Downward...";
	report->Begin("Running FastDownward");
	auto runRes = DownwardRunner::RunDownward(config, CommonInterface::TempDomainName, CommonInterface::TempProblemName);
	if (runRes != DownwardRunner::FoundPlan) {
		cout << "   ✕" << endl;
		cout << "No solution could be found for the plan" << endl;
		return;
	}
	else {
		t = report->Stop();
		cout << "   ✓ " << t << "ms" << endl;

		if (config.validatePlans) {
			// Check to make sure the reformulated plan also matches the reformulated problem and domain
			cout << "Validate reformulated SAS plan...";
			report->Begin("Validating reformulated SAS plan");
			auto reformulatedSASValidatorResult = PlanValidator::ValidatePlan(config, CommonInterface::TempDomainName, CommonInterface::TempProblemName, CommonInterface::FastDownwardSASName);
			if (reformulatedSASValidatorResult != PlanValidator::PlanMatch) {
				cout << "   ✕" << endl;
				cout << "Output plan is not valid for reformulated domain and problem!" << endl;
				return;
			}
			t = report->Stop();
			cout << "   ✓ " << t << "ms" << endl;
		}

		// Parse the output SAS plan
		cout << "Parse SAS Plan...";
		report->Begin("Parse SAS plan");
		SASParser sasParser;
		filesystem::path sasPath = filesystem::path(CommonInterface::FastDownwardSASName);
		SASPlan reformulatedSASPlan = sasParser.Parse(sasPath);
		t = report->Stop();
		cout << "   ✓ " << t << "ms" << endl;

		// Rebuild the SAS Plan
		cout << "Rebuild the SAS plan...";
		report->Begin("Rebuild SAS plan");
		SASPlan outputPlan = Reformulator->RebuildSASPlan(&reformulatedSASPlan);
		t = report->Stop();
		cout << "   ✓ " << t << "ms" << endl;

		// Output the new SAS plan
		cout << "Output new SAS Plan...";
		report->Begin("Output SAS plan");
		SASCodeGenerator sasGenerator;
		sasGenerator.GenerateCode(outputPlan, CommonInterface::OutputSASName);
		t = report->Stop();
		cout << "   ✓ " << t << "ms" << endl;

		if (config.validatePlans) {
			// Validate reformulated plan works with original domain and problem
			cout << "Validate new SAS plan...";
			report->Begin("Validate new SAS plan");
			auto newSASValidatorResult = PlanValidator::ValidatePlan(config, config.domainFile, config.problemFile, CommonInterface::OutputSASName);
			if (newSASValidatorResult != PlanValidator::PlanMatch) {
				cout << "   ✕" << endl;
				cout << "Output plan is not valid for original domain and problem!" << endl;
				return;
			}
			t = report->Stop();
			cout << "   ✓" << t << "ms" << endl;
		}
	}
}
