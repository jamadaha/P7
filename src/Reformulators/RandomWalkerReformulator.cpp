#include "RandomWalkerReformulator.hh"

using namespace std;

PDDLInstance RandomWalkerReformulator::ReformulatePDDL(PDDLInstance* instance) {
	// Walk the PDDL
	auto paths = PerformWalk(instance);

	// Find Entangelements
	auto candidates = FindEntanglements(instance, paths);

	// Generate new Macros
	auto newInstance = GenerateMacros(candidates, instance);

	return newInstance;
}

std::vector<Path> RandomWalkerReformulator::PerformWalk(PDDLInstance* instance) {
	// Walk the PDDL
	RandomHeuristic<PDDLActionInstance>* heu = new RandomHeuristic<PDDLActionInstance>(PDDLContext(instance->domain, instance->problem));
	BaseWidthFunction* widthFunc;
	if (Configs->ReformulatorTime.Content == -1)
		widthFunc = new ConstantWidthFunction(100);
	else
		widthFunc = new TimeWidthFunction(Configs->ReformulatorTime.Content);
	auto depthFunction = new ConstantDepthFunction(100, *instance);
	std::vector<Path> paths;
	unsigned int totalActionCount = 0;
	unsigned int totalIterations = 0;
	auto startTime = chrono::steady_clock::now();
	for (int i = 0; i < widthFunc->GetWidth(); i++) {
		Walker walker = Walker(instance,
			ActionGenerator(instance->domain, instance->problem),
			heu,
			depthFunction);
		paths.push_back(walker.Walk());

		// Debug info
		if (Configs->DebugMode.Content) {
			totalActionCount += walker.totalActions;
			totalIterations++;
		}
	}
	auto endTime = chrono::steady_clock::now();

	// Print debug info
	if (Configs->DebugMode.Content) {
		auto ellapsed = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();
		ConsoleHelper::PrintDebugInfo("[Walker] Total walk time:         " + to_string(ellapsed) + "ms", 1);
		double iterationsPrSecond = (totalIterations * 1000) / ellapsed;
		ConsoleHelper::PrintDebugInfo("[Walker] Total walker iterations: " + to_string(totalIterations) + " [" + to_string(iterationsPrSecond) + "/s]", 1);
		double actionsPrSecond = (totalActionCount * 1000) / ellapsed;
		ConsoleHelper::PrintDebugInfo("[Walker] Total actions Generated: " + to_string(totalActionCount) + " [" + to_string(actionsPrSecond) + "/s]", 1);
	}

	free(heu); free(widthFunc); free(depthFunction);

	return paths;
}

unordered_set<vector<PDDLActionInstance>> RandomWalkerReformulator::FindEntanglements(PDDLInstance* instance, vector<Path> paths) {
	EntanglementFinder entFinder;
	auto startTime = chrono::steady_clock::now();
	auto candidates = entFinder.FindEntangledCandidates(instance, paths);
	auto endTime = chrono::steady_clock::now();

	// Print debug info
	if (Configs->DebugMode.Content) {
		unsigned int totalActions = 0;
		for (int i = 0; i < paths.size(); i++)
			totalActions += paths[i].steps.size();

		auto ellapsed = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();
		ConsoleHelper::PrintDebugInfo("[Entanglement Finder] Total search time:         " + to_string(ellapsed) + "ms", 1);
		ConsoleHelper::PrintDebugInfo("[Entanglement Finder] Found a total of " + to_string(candidates.size()) + " candidates out of " + to_string(paths.size()) + " paths that has " + to_string(totalActions) + " steps", 1);
	}

	return candidates;
}

PDDLInstance RandomWalkerReformulator::GenerateMacros(unordered_set<vector<PDDLActionInstance>> candidates, PDDLInstance* instance) {
	PDDLInstance newInstance(instance->domain, instance->problem);
	return newInstance;
}

SASPlan RandomWalkerReformulator::RebuildSASPlan(SASPlan* reformulatedSAS) {
	// Do Something and give a "corrected" SAS plan back
	SASPlan newPlan(reformulatedSAS->actions, reformulatedSAS->cost);
	return newPlan;
} 