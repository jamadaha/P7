#include "CommonInterface.hh"

using namespace std;

InterfaceStep<BaseReformulator*> CommonInterface::GetReformulator(int reformulatorIndex) {
	ConsoleHelper::PrintInfo("Finding reformulator algorithm...");
	Report->Begin("Finding reformulator");
	BaseReformulator* reformulator;
	if (config.GetItem<vector<string>>("reformulator").at(reformulatorIndex) == "sameoutput")
		reformulator = new SameOutputReformulator(&config, Report);
	else if (config.GetItem<vector<string>>("reformulator").at(reformulatorIndex) == "greedyWalker")
		reformulator = new GreedyWalkerReformulator(&config, Report);
	else if (config.GetItem<vector<string>>("reformulator").at(reformulatorIndex) == "greedyResumeWalker")
		reformulator = new GreedyResumeWalkerReformulator(&config, Report);
	else if (config.GetItem<vector<string>>("reformulator").at(reformulatorIndex) == "queueWalker")
		reformulator = new QueueWalkerReformulator(&config, Report);
	else if (config.GetItem<vector<string>>("reformulator").at(reformulatorIndex) == "probeWalker")
		reformulator = new ProbeWalkerReformulator(&config, Report);
	else if (config.GetItem<vector<string>>("reformulator").at(reformulatorIndex) == "regressor")
		reformulator = new RegressionReformulator(&config, Report);
	else if (config.GetItem<vector<string>>("reformulator").at(reformulatorIndex) == "partialRegressor")
		reformulator = new PartialRegressionReformulator(&config, Report);
	else if (config.GetItem<vector<string>>("reformulator").at(reformulatorIndex) == "stepBackWalker")
		reformulator = new StepBackWalkerReformulator(&config, Report);
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

InterfaceStep<PDDL::Instance*> CommonInterface::ParsePDDLFiles() {
	ConsoleHelper::PrintInfo("Parsing PDDL files...");
	Report->Begin("Parsing PDDL Files");
	ExternalParser parser;
	auto result = parser.Parse(config.GetItem<filesystem::path>("domain"), config.GetItem<filesystem::path>("problem"));
	Report->Stop();
	return InterfaceStep<PDDL::Instance*>(result);
}

InterfaceStep<void> CommonInterface::RunIteratively(BaseReformulator* reformulator, PDDL::Instance* instance) {
	int timeLeft = config.GetItem<int>("totalTimeLimit") * 1000;
	int currentIncrementTimeLimit = config.GetItem<int>("startIncrement") * 1000;

	int iterativeProcess = Report->Begin("Solving Problem");

	CommonInterface::ReformulatorRunResultResult runRes;
	int counter = 1;
	while (timeLeft > 0) {
		int reformulatorTimeLimit = (currentIncrementTimeLimit * 2) * config.GetItem<double>("timelimitSplit");
		int downwardTimeLimit = (currentIncrementTimeLimit * 2) - reformulatorTimeLimit;

		int iterationID = Report->Begin("Iteration " + to_string(counter), iterativeProcess);
		ConsoleHelper::PrintInfo("Iteration " + to_string(counter) + "(reformulator: " + to_string(reformulatorTimeLimit) + "ms, downward: " + to_string(downwardTimeLimit) + "ms)");

		// Run an iteration of our reformulation method
		runRes = RunSingle(reformulator, instance, iterationID, reformulatorTimeLimit, downwardTimeLimit).Data;
		Report->Stop(iterationID);
		if (runRes == ReformulatorRunResultResult::ReformulatorFailed || runRes == ReformulatorRunResultResult::FoundPlan) {
			break;
		}

		// Subtract the time it took to execute this iteration from the total allowed time
		timeLeft -= currentIncrementTimeLimit * 2;
		// Increase the time limit for the next iteration
		currentIncrementTimeLimit *= config.GetItem<int>("incrementModifier");
		// If the next iteration will take too long, only spend the amount of time possible within the overall time limit
		if (timeLeft - currentIncrementTimeLimit * 2 < 0)
			currentIncrementTimeLimit = timeLeft / 2;
		counter++;
	}

	switch (runRes) {
	case CommonInterface::ReformulatorRunResultResult::ReformulatorFailed:
		Report->Stop(iterativeProcess, ReportData("None", "-1", "false"));
		ConsoleHelper::PrintError("Something in the reformulator failed! Use debug mode to get more info");
		return InterfaceStep<void>(false);
	case CommonInterface::ReformulatorRunResultResult::DidNotFindPlan:
		Report->Stop(iterativeProcess, ReportData("None", "-1", "false"));
		ConsoleHelper::PrintError("Fast downward did not find a plan in time!");
		return InterfaceStep<void>(false);
	}

	Report->Stop(iterativeProcess, ReportData("None", "-1", "true"));
	return InterfaceStep<void>();
}

InterfaceStep<void> CommonInterface::RunDirect(BaseReformulator* reformulator, PDDL::Instance* instance) {
	int directProcess = Report->Begin("Solving Problem");
	int timeLimit = config.GetItem<int>("totalTimeLimit") * 1000;

	auto runRes = RunSingle(reformulator, instance, directProcess, timeLimit, timeLimit).Data;
	switch (runRes) {
	case CommonInterface::ReformulatorRunResultResult::ReformulatorFailed:
		Report->Stop(directProcess, ReportData("None", "-1", "false"));
		ConsoleHelper::PrintError("Something in the reformulator failed! Use debug mode to get more info");
		return InterfaceStep<void>(false);
	case CommonInterface::ReformulatorRunResultResult::DidNotFindPlan:
		Report->Stop(directProcess, ReportData("None", "-1", "false"));
		ConsoleHelper::PrintError("Fast downward did not find a plan in time!");
		return InterfaceStep<void>(false);
	}

	Report->Stop(directProcess, ReportData("None", "-1", "true"));
	return InterfaceStep<void>();
}

InterfaceStep<CommonInterface::ReformulatorRunResultResult> CommonInterface::RunSingle(BaseReformulator* reformulator, PDDL::Instance* instance, int reportID, int reformulatorTimeLimit, int downwardTimeLimit) {
	ConsoleHelper::PrintInfo("Reformulating PDDL...", 1);
	int reformulationID = Report->Begin("Reformulation of PDDL", reportID);
	reformulator->ReportID = reformulationID;
	reformulator->TimeLimit = reformulatorTimeLimit;
	PDDL::Instance reformulatedInstance = reformulator->ReformulatePDDL(instance);
	Report->Stop();
	Report->Stop(reformulationID);
	if (reformulator->DidEncounterErrors()) {
		return InterfaceStep<CommonInterface::ReformulatorRunResultResult>(CommonInterface::ReformulatorRunResultResult::ReformulatorFailed, false);
	}

	// Generate new PDDL files
	ConsoleHelper::PrintInfo("Generating PDDL files...", 1);
	Report->Begin("Generating PDDL", reportID);
	PDDL::CodeGenerator pddlGenerator = PDDL::CodeGenerator(PDDL::DomainCodeGenerator(reformulatedInstance.domain), PDDL::ProblemCodeGenerator(reformulatedInstance.domain, reformulatedInstance.problem));
	pddlGenerator.GenerateCode(reformulatedInstance, CommonInterface::TempDomainName, CommonInterface::TempProblemName);
	Report->Stop();

	// Throw the new pddl files into Fast Downward
	ConsoleHelper::PrintInfo("Run new PDDL files with Fast Downward...", 1);
	Report->Begin("Running FastDownward", reportID);
	DownwardRunner runner = DownwardRunner();
	runner.RunDownward(&config, CommonInterface::TempDomainName, CommonInterface::TempProblemName, downwardTimeLimit);
	auto runRes = runner.ParseDownwardLog();
	Report->Stop();
	if (runRes != DownwardRunner::FoundPlan) {
		return InterfaceStep<CommonInterface::ReformulatorRunResultResult>(CommonInterface::ReformulatorRunResultResult::DidNotFindPlan, false);
	}
	return InterfaceStep<CommonInterface::ReformulatorRunResultResult>(CommonInterface::ReformulatorRunResultResult::FoundPlan);
}

InterfaceStep<void> CommonInterface::ValidatePlans(string domainFile, string problemFile, string sasFile, string reportName) {
	ConsoleHelper::PrintDebugInfo(reportName);
	int parent = Report->Begin(reportName);
	auto reformulatedSASValidatorResult = PlanValidator::ValidatePlan(config, domainFile, problemFile, sasFile);
	if (reformulatedSASValidatorResult != PlanValidator::PlanMatch) {
		Report->Stop(parent, ReportData("None", "-1", "false"));
		ConsoleHelper::PrintDebugError("Output plan is not valid for reformulated domain and problem!");
		return InterfaceStep<void>(false);
	}
	Report->Stop(parent, ReportData("None", "-1", "true"));
	return InterfaceStep<void>(true);
}

InterfaceStep<SAS::Plan> CommonInterface::ParseSASPlan() {
	ConsoleHelper::PrintInfo("Parsing SAS Plan...");
	Report->Begin("Parse SAS plan");
	SAS::Parser sasParser;
	filesystem::path sasPath = filesystem::path(CommonInterface::FastDownwardSASName);
	SAS::Plan reformulatedSASPlan = sasParser.Parse(sasPath);
	Report->Stop(ReportData("None", to_string(reformulatedSASPlan.cost)));
	return InterfaceStep<SAS::Plan>(reformulatedSASPlan);
}

InterfaceStep<SAS::Plan> CommonInterface::RebuildSASPlan(SAS::Plan* reformulatedSASPlan, BaseReformulator* reformulator, PDDL::Instance* instance) {
	ConsoleHelper::PrintInfo("Rebuilding the SAS plan...");
	Report->Begin("Rebuild SAS plan");
	SAS::Plan outputPlan = reformulator->RebuildSASPlan(instance, reformulatedSASPlan);
	Report->Stop(ReportData("None", to_string(outputPlan.cost)));
	Report->Begin("Plan Length Difference");
	Report->Stop(ReportData("None", to_string(outputPlan.cost - reformulatedSASPlan->cost)));
	Report->Begin("Macros Generated");
	Report->Stop(ReportData("None", to_string(reformulator->GetMacrosGenerated())));
	Report->Begin("Macros Used");
	Report->Stop(ReportData("None", to_string(outputPlan.macrosUsed)));
	return InterfaceStep<SAS::Plan>(outputPlan);
}

InterfaceStep<void> CommonInterface::GenerateNewSASPlan(SAS::Plan outputPlan) {
	ConsoleHelper::PrintInfo("Output new SAS Plan...");
	Report->Begin("Output SAS plan");
	SAS::CodeGenerator sasGenerator;
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

	if (!isDirect) {
		auto runIterativelyStep = RunIteratively(getReformulatorStep.Data, parsePDDLFilesStep.Data);
		if (!runIterativelyStep.RanWithoutErrors)
			return CommonInterface::RunResult::ErrorsEncountered;
	}
	else {
		auto runNonIterativelyStep = RunDirect(getReformulatorStep.Data, parsePDDLFilesStep.Data);
		if (!runNonIterativelyStep.RanWithoutErrors)
			return CommonInterface::RunResult::ErrorsEncountered;
	}

	if (config.GetItem<bool>("validate")) {
		auto validateSASPlanStep = ValidatePlans(CommonInterface::TempDomainName, CommonInterface::TempProblemName, CommonInterface::FastDownwardSASName, "Validating reformulated plan");
		if (!validateSASPlanStep.RanWithoutErrors)
			return CommonInterface::RunResult::ErrorsEncountered;
	}

	auto parseSASPlanStep = ParseSASPlan();
	if (!parseSASPlanStep.RanWithoutErrors)
		return CommonInterface::RunResult::ErrorsEncountered;

	auto rebuildSASPlanStep = RebuildSASPlan(&parseSASPlanStep.Data, getReformulatorStep.Data, parsePDDLFilesStep.Data);
	if (!rebuildSASPlanStep.RanWithoutErrors)
		return CommonInterface::RunResult::ErrorsEncountered;

	auto generateNewSASPlanStep = GenerateNewSASPlan(rebuildSASPlanStep.Data);
	if (!generateNewSASPlanStep.RanWithoutErrors)
		return CommonInterface::RunResult::ErrorsEncountered;

	if (config.GetItem<bool>("validate")) {
		auto validateSASPlanStep = ValidatePlans(config.GetItem<filesystem::path>("domain"), config.GetItem<filesystem::path>("problem"), CommonInterface::OutputSASName, "Validating rebuilded plan");
		if (!validateSASPlanStep.RanWithoutErrors)
			return CommonInterface::RunResult::ErrorsEncountered;
	}

	return CommonInterface::RunResult::RanWithoutErrors;
}
