#include "CommonInterface.hh"

using namespace std;

InterfaceStep<BaseReformulator*> CommonInterface::GetReformulator(int reformulatorIndex) {
	ConsoleHelper::PrintInfo("Finding reformulator algorithm...");
	Report->Begin("Finding reformulator");
	BaseReformulator* reformulator;
	if (config.GetItem<vector<string>>("reformulator").at(reformulatorIndex) == "sameoutput") {
		reformulator = new SameOutputReformulator(&config, Report);
	}
	else 	if (config.GetItem<vector<string>>("reformulator").at(reformulatorIndex) == "walker") {
		reformulator = new WalkerReformulator(&config, Report);
	}
	else {
		ConsoleHelper::PrintError("Reformulator not found! Reformulator: " + config.GetItem<string>("reformulator"));
		return InterfaceStep<BaseReformulator*>(reformulator, false);
	}
	Report->Stop();
	return InterfaceStep<BaseReformulator*>(reformulator);
}

InterfaceStep<void> CommonInterface::CheckFilePaths() {
	ConsoleHelper::PrintDebugInfo("Checking filepaths from the config...");
	Report->Begin("Checking Filepaths");
	string notFoundPath = PathsChecker::IsPathsOk(&config);
	if (notFoundPath != "") {
		ConsoleHelper::PrintDebugError("Some file paths where not found! Not found path: " + notFoundPath);
		return InterfaceStep<void>(false);
	}
	Report->Stop();
	return InterfaceStep<void>();
}

InterfaceStep<PDDLDriver*> CommonInterface::ParsePDDLFiles() {
	ConsoleHelper::PrintInfo("Parsing PDDL files...");
	PDDLDriver* originalDriver = new PDDLDriver();
	Report->Begin("Parsing PDDL Files");
	if (originalDriver->parse(config.GetItem<filesystem::path>("domain"))) {
		ConsoleHelper::PrintError("Error parsing the domain file!");
		return InterfaceStep<PDDLDriver*>(originalDriver, false);
	}
	if (originalDriver->parse(config.GetItem<filesystem::path>("problem"))) {
		ConsoleHelper::PrintError("Error parsing the problem file!");
		return InterfaceStep<PDDLDriver*>(originalDriver, false);
	}
	Report->Stop();
	return InterfaceStep<PDDLDriver*>(originalDriver);
}

InterfaceStep<PDDLInstance*> CommonInterface::ConvertPDDLFormat(PDDLDriver* driver) {
	ConsoleHelper::PrintInfo("Converting PDDL format...");
	Report->Begin("Converison of PDDL format");
	static PDDLDomain domain = PDDLConverter::Convert(driver->domain);
	static PDDLProblem problem = PDDLConverter::Convert(&domain, driver->problem);
	PDDLInstance* instance = new PDDLInstance(&domain, &problem);
	Report->Stop();
	return InterfaceStep<PDDLInstance*>(instance);
}

InterfaceStep<void> CommonInterface::RunIteratively(BaseReformulator* reformulator, PDDLInstance* instance) {
	int timeLimit = config.GetItem<int>("incrementLimit");
	int currentIncrementTimeLimit = config.GetItem<int>("startIncrement");
	bool isDirect = false;

	int iterativeProcess = Report->Begin("Reformulating Iteratively");

	if (isDirect)
		currentIncrementTimeLimit = timeLimit;

	DownwardRunner::DownwardRunnerResult runRes;
	int counter = 1;
	while (currentIncrementTimeLimit <= timeLimit) {
		int iterationID = Report->Begin("Iteration " + to_string(counter), iterativeProcess);
		ConsoleHelper::PrintInfo("Iteration " + to_string(counter) + "(" + to_string(currentIncrementTimeLimit) + "s)");
		reformulator->TimeLimit = currentIncrementTimeLimit;

		// Reformulate the PDDL file
		ConsoleHelper::PrintInfo("Reformulating PDDL...", 1);
		int reformulationID= Report->Begin("Reformulation of PDDL", iterationID);
		reformulator->ReportID = reformulationID;
		reformulator->Iteration = counter;
		PDDLInstance reformulatedInstance = reformulator->ReformulatePDDL(instance);
		Report->Stop(reformulationID);

		// Generate new PDDL files
		ConsoleHelper::PrintInfo("Generating PDDL files...", 1);
		Report->Begin("Generating PDDL", iterationID);
		PDDLCodeGenerator pddlGenerator = PDDLCodeGenerator(PDDLDomainCodeGenerator(reformulatedInstance.domain), PDDLProblemCodeGenerator(reformulatedInstance.domain, reformulatedInstance.problem));
		pddlGenerator.GenerateCode(reformulatedInstance, CommonInterface::TempDomainName, CommonInterface::TempProblemName);
		Report->Stop();

		// Throw the new pddl files into Fast Downward
		ConsoleHelper::PrintInfo("Run new PDDL files with Fast Downward...", 1);
		Report->Begin("Running FastDownward", iterationID);
		DownwardRunner runner = DownwardRunner();
		runner.RunDownward(config, CommonInterface::TempDomainName, CommonInterface::TempProblemName, currentIncrementTimeLimit);
		runRes = runner.ParseDownwardLog();
		Report->Stop();
		Report->Stop(iterationID);
		if (runRes == DownwardRunner::FoundPlan) {
			break;
		}
		currentIncrementTimeLimit *= config.GetItem<int>("incrementModifier");
		counter++;
	}
	Report->Stop(iterativeProcess);
	if (runRes != DownwardRunner::FoundPlan) {
		ConsoleHelper::PrintError("Fast downward did not find a plan in time!");
		return InterfaceStep<void>(false);
	}
	return InterfaceStep<void>();
}

InterfaceStep<void> CommonInterface::RunSingle(BaseReformulator* reformulator, PDDLInstance* instance) {
	ConsoleHelper::PrintInfo("Reformulating PDDL...", 1);
	int reformulationID = Report->Begin("Reformulation of PDDL");
	reformulator->ReportID = reformulationID;
	PDDLInstance reformulatedInstance = reformulator->ReformulatePDDL(instance);
	Report->Stop();

	// Generate new PDDL files
	ConsoleHelper::PrintInfo("Generating PDDL files...", 1);
	Report->Begin("");
	PDDLCodeGenerator pddlGenerator = PDDLCodeGenerator(PDDLDomainCodeGenerator(reformulatedInstance.domain), PDDLProblemCodeGenerator(reformulatedInstance.domain, reformulatedInstance.problem));
	pddlGenerator.GenerateCode(reformulatedInstance, CommonInterface::TempDomainName, CommonInterface::TempProblemName);
	Report->Stop();

	// Throw the new pddl files into Fast Downward
	ConsoleHelper::PrintInfo("Run new PDDL files with Fast Downward...", 1);
	Report->Begin("");
	DownwardRunner runner = DownwardRunner();
	runner.RunDownward(config, CommonInterface::TempDomainName, CommonInterface::TempProblemName, -1);
	auto runRes = runner.ParseDownwardLog();
	Report->Stop();
	if (runRes != DownwardRunner::FoundPlan) {
		ConsoleHelper::PrintError("Fast downward did not find a plan!");
		return InterfaceStep<void>(false);
	}
	return InterfaceStep<void>();
}

InterfaceStep<void> CommonInterface::ValidatePlans(string domainFile, string problemFile, string sasFile) {
	ConsoleHelper::PrintDebugInfo("Validate reformulated SAS plan...");
	Report->Begin("Validating reformulated SAS plan");
	auto reformulatedSASValidatorResult = PlanValidator::ValidatePlan(config, domainFile, problemFile, sasFile);
	Report->Stop();
	if (reformulatedSASValidatorResult != PlanValidator::PlanMatch) {
		ConsoleHelper::PrintDebugError("Output plan is not valid for reformulated domain and problem!");
		return InterfaceStep<void>(false);
	}
	return InterfaceStep<void>(true);
}

InterfaceStep<SASPlan> CommonInterface::ParseSASPlan() {
	ConsoleHelper::PrintInfo("Parsing SAS Plan...");
	Report->Begin("Parse SAS plan");
	SASParser sasParser;
	filesystem::path sasPath = filesystem::path(CommonInterface::FastDownwardSASName);
	SASPlan reformulatedSASPlan = sasParser.Parse(sasPath);
	Report->Stop();
	return InterfaceStep<SASPlan>(reformulatedSASPlan);
}

InterfaceStep<SASPlan> CommonInterface::RebuildSASPlan(SASPlan* reformulatedSASPlan, BaseReformulator* reformulator, PDDLInstance* instance) {
	ConsoleHelper::PrintInfo("Rebuilding the SAS plan...");
	Report->Begin("Rebuild SAS plan");
	SASPlan outputPlan = reformulator->RebuildSASPlan(instance, reformulatedSASPlan);
	Report->Stop();
	return InterfaceStep<SASPlan>(outputPlan);
}

InterfaceStep<void> CommonInterface::GenerateNewSASPlan(SASPlan outputPlan) {
	ConsoleHelper::PrintInfo("Output new SAS Plan...");
	Report->Begin("Output SAS plan");
	SASCodeGenerator sasGenerator;
	sasGenerator.GenerateCode(outputPlan, CommonInterface::OutputSASName);
	Report->Stop();
	return InterfaceStep<void>();
}

enum CommonInterface::RunResult CommonInterface::Run(int reformulatorIndex) {

	auto getReformulatorStep = GetReformulator(reformulatorIndex);
	if (!getReformulatorStep.RanWithoutErrors)
		return CommonInterface::RunResult::ErrorsEncountered;

	if (config.GetItem<bool>("debugmode")) {
		auto checkFilePathsStep = CheckFilePaths();
		if (!checkFilePathsStep.RanWithoutErrors)
			return CommonInterface::RunResult::ErrorsEncountered;
	}

	auto parsePDDLFilesStep = ParsePDDLFiles();
	if (!parsePDDLFilesStep.RanWithoutErrors)
		return CommonInterface::RunResult::ErrorsEncountered;

	auto convertPDDLFormatStep = ConvertPDDLFormat(parsePDDLFilesStep.Data);
	if (!convertPDDLFormatStep.RanWithoutErrors)
		return CommonInterface::RunResult::ErrorsEncountered;

	if (config.GetItem<bool>("runIteratively")) {
		auto runIterativelyStep = RunIteratively(getReformulatorStep.Data, convertPDDLFormatStep.Data);
		if (!runIterativelyStep.RanWithoutErrors)
			return CommonInterface::RunResult::ErrorsEncountered;
	}
	else {
		auto runNonIterativelyStep = RunSingle(getReformulatorStep.Data, convertPDDLFormatStep.Data);
		if (!runNonIterativelyStep.RanWithoutErrors)
			return CommonInterface::RunResult::ErrorsEncountered;
	}

	if (config.GetItem<bool>("debugmode")) {
		auto validateSASPlanStep = ValidatePlans(CommonInterface::TempDomainName, CommonInterface::TempProblemName, CommonInterface::FastDownwardSASName);
		if (!validateSASPlanStep.RanWithoutErrors)
			return CommonInterface::RunResult::ErrorsEncountered;
	}

	auto parseSASPlanStep = ParseSASPlan();
	if (!parseSASPlanStep.RanWithoutErrors)
		return CommonInterface::RunResult::ErrorsEncountered;

	auto rebuildSASPlanStep = RebuildSASPlan(&parseSASPlanStep.Data, getReformulatorStep.Data, convertPDDLFormatStep.Data);
	if (!rebuildSASPlanStep.RanWithoutErrors)
		return CommonInterface::RunResult::ErrorsEncountered;

	auto generateNewSASPlanStep = GenerateNewSASPlan(rebuildSASPlanStep.Data);
	if (!generateNewSASPlanStep.RanWithoutErrors)
		return CommonInterface::RunResult::ErrorsEncountered;

	if (config.GetItem<bool>("debugmode")) {
		auto validateSASPlanStep = ValidatePlans(config.GetItem<filesystem::path>("domain"), config.GetItem<filesystem::path>("problem"), CommonInterface::OutputSASName);
		if (!validateSASPlanStep.RanWithoutErrors)
			return CommonInterface::RunResult::ErrorsEncountered;
	}

	return CommonInterface::RunResult::RanWithoutErrors;
}
