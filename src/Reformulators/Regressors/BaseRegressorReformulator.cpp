#include "BaseRegressorReformulator.hh"

PDDLInstance BaseRegressorReformulator::ReformulatePDDL(PDDLInstance* instance) {
    bool debugMode = Configs->GetItem<bool>("debugmode");

	if (!HaveRunPreprocessor)
		GetMutexes(instance, debugMode);

    FindPaths(instance, debugMode);
    std::vector<EntanglementOccurance> candidates = FindEntanglements(instance, debugMode);
    GenerateMacros(instance, &candidates, debugMode);
    PDDLInstance macroInstance = GenerateMacroInstance(instance, &macros, debugMode);

    return macroInstance;
}

void BaseRegressorReformulator::FindPaths(PDDLInstance *instance, bool debugMode) {
    auto tempPaths = PerformRegression(instance, debugMode);
    for (int i = 0; i < tempPaths.size(); i++)
    this->paths.push_back(tempPaths.at(i));
}

void BaseRegressorReformulator::GetMutexes(PDDLInstance* instance, bool debugMode) {
	if (debugMode)
		ConsoleHelper::PrintDebugInfo("Getting mutexes...", debugIndent);
	auto domain = Configs->GetItem<std::filesystem::path>("domain");
	auto problem = Configs->GetItem<std::filesystem::path>("problem");
	DownwardRunner runner = DownwardRunner();
	runner.RunTranslator(Configs, domain.c_str(), problem.c_str());
	H2Runner h2Runner = H2Runner(instance);
	static PDDLMutex mutexes = h2Runner.RunH2(Configs);
	instance->mutexes = &mutexes;
	HaveRunPreprocessor = true;
}