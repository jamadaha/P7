#include "BaseRegressorReformulator.hh"

PDDL::Instance BaseRegressorReformulator::ReformulatePDDL(PDDL::Instance* instance) {
    bool debugMode = Configs->GetItem<bool>("debugmode");

	if (!HaveRunPreprocessor)
		GetMutexes(instance, debugMode);

    FindPaths(instance, debugMode);

	// Entanglement Finding
    std::vector<JointPaths::JointPath> candidates = FindEntanglements(instance, debugMode);

	// Macro Generation
	PDDL::Instance macroInstance = GenerateMacros(instance, &candidates, debugMode);

    return macroInstance;
}

void BaseRegressorReformulator::FindPaths(PDDL::Instance *instance, bool debugMode) {
    int regressID = Report->Begin("Walking", ReportID);	

    auto tempPaths = PerformRegression(instance, debugMode);
    for (int i = 0; i < tempPaths.size(); i++)
        this->paths.push_back(tempPaths.at(i));

    auto ellapsed = Report->Stop(regressID);

    ValidatePaths(instance, regressID, debugMode);
}

void BaseRegressorReformulator::GetMutexes(PDDL::Instance* instance, bool debugMode) {
	if (debugMode)
		ConsoleHelper::PrintDebugInfo("Getting mutexes...", debugIndent);
	auto domain = Configs->GetItem<std::filesystem::path>("domain");
	auto problem = Configs->GetItem<std::filesystem::path>("problem");
	DownwardRunner runner = DownwardRunner();
	runner.RunTranslator(Configs, domain.c_str(), problem.c_str());
	H2Runner h2Runner = H2Runner(instance);
	static PDDL::Mutex mutexes = h2Runner.RunH2(Configs);
	instance->mutexes = &mutexes;
	HaveRunPreprocessor = true;
}