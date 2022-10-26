#include "RandomWalkerReformulator.hh"

using namespace std;

PDDLInstance RandomWalkerReformulator::ReformulatePDDL(PDDLInstance* instance) {
	// Walk the PDDL
	auto paths = PerformWalk(instance);

	// Find Entangelements
	auto candidates = FindEntanglements(&paths, instance);

	// Generate new Macros
	auto newInstance = GenerateMacros(candidates, instance);

	return newInstance;
}

std::vector<Path> RandomWalkerReformulator::PerformWalk(PDDLInstance* instance) {
	// Walk the PDDL
	RandomHeuristic<PDDLActionInstance>* heu = new RandomHeuristic<PDDLActionInstance>(PDDLContext(instance->domain, instance->problem));
	BaseWidthFunction* widthFunc;
	if (Configs->GetInteger("timelimit") == -1)
		widthFunc = new ConstantWidthFunction(100);
	else
		widthFunc = new TimeWidthFunction(Configs->GetInteger("timelimit"));
	auto depthFunction = new ConstantDepthFunction(100, *instance);
	std::vector<Path> paths;
	unsigned int totalActionCount = 0;
	unsigned int totalIterations = 0;
	auto startTime = chrono::steady_clock::now();
	ProgressBarHelper* bar;
	if (Configs->GetBool("debugmode")) {
		if (Configs->GetInteger("timelimit") == -1)
			bar = new ProgressBarHelper(widthFunc->GetWidth(), "Walking", 1);
		else
			bar = new ProgressBarHelper(Configs->GetInteger("timelimit"), "Walking", 1);
	}

	for (int i = 0; i < widthFunc->GetWidth(); i++) {
		Walker walker = Walker(instance,
			ActionGenerator(instance->domain, instance->problem),
			heu,
			depthFunction);
		auto walk = walker.Walk(Configs);
		if (walk.steps.size() > 5) {
			paths.push_back(walk);
			// Debug info
			if (Configs->GetBool("debugmode")) {
				totalActionCount += walker.totalActions;
				totalIterations++;
			}
		}
		if (Configs->GetBool("debugmode")) {
			if (Configs->GetInteger("timelimit") == -1) {
				bar->Update();
			}
			else {
				auto curEndTime = chrono::steady_clock::now();
				auto thisRound = chrono::duration_cast<chrono::milliseconds>(curEndTime - startTime).count();
				bar->SetTo(thisRound);
			}
		}
	}
	if (Configs->GetBool("debugmode"))
		bar->End();
	auto endTime = chrono::steady_clock::now();

	// Print debug info
	if (Configs->GetBool("debugmode")) {
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

unordered_map<size_t, EntanglementOccurance> RandomWalkerReformulator::FindEntanglements(vector<Path>* paths, PDDLInstance* instance) {
	EntanglementFinder entFinder;

	if (Configs->GetBool("debugmode")) {
		ProgressBarHelper* bar;
		entFinder.OnNewLevel = [&](int level, int outOf) {
			bar = new ProgressBarHelper(outOf, "Finding Entanglements (level " + to_string(level) + ")", 1);
		};
		entFinder.OnLevelIteration = [&](int current, int outOf) {
			bar->Update();
		};
		entFinder.OnLevelEnd = [&]() {
			bar->End();
		};
	}

	auto startTime = chrono::steady_clock::now();
	auto candidates = entFinder.FindEntangledCandidates(paths);
	auto endTime = chrono::steady_clock::now();

	if (Configs->GetBool("printentanglersteps")) {
		ConsoleHelper::PrintDebugInfo("[Entanglement Finder] Entanglements:", 1);
		for (auto i = candidates.begin(); i != candidates.end(); i++) {
			string actionStr = "";
			for (int j = 0; j < (*i).second.Chain.size(); j++) {
				auto item = (*i).second.Chain.at(j);
				string paramStr = "";
				for (int l = 0; l < item->objects.size(); l++) {
					paramStr += instance->problem->objects[item->objects[l]];
					if (l != item->objects.size() - 1)
						paramStr += ", ";
				}
				actionStr += item->action->name + "(" + paramStr + ")";
				if (j != (*i).second.Chain.size() - 1)
					actionStr += " -> ";
			}
			ConsoleHelper::PrintDebugInfo("[Entanglement Finder] " + to_string((*i).second.Occurance) + " : " + to_string((*i).second.BetweenDifferentPaths) + " : " + actionStr, 2);
		}
	}
	if (Configs->GetBool("debugmode")) {
		unsigned int totalActions = 0;
		for (int i = 0; i < paths->size(); i++)
			totalActions += paths->at(i).steps.size();

		auto ellapsed = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();
		ConsoleHelper::PrintDebugInfo("[Entanglement Finder] Total search time:         " + to_string(ellapsed) + "ms", 1);
		ConsoleHelper::PrintDebugInfo("[Entanglement Finder] Total Levels:              " + to_string(entFinder.TotalLevels()), 1);
		double comparisonsPrSecond = (entFinder.TotalComparisons() * 1000) / ellapsed;
		ConsoleHelper::PrintDebugInfo("[Entanglement Finder] Total Comparisons:         " + to_string(entFinder.TotalComparisons()) + " [" + to_string(comparisonsPrSecond) + "/s]", 1);
		ConsoleHelper::PrintDebugInfo("[Entanglement Finder] Total Candidates:          " + to_string(candidates.size()) + " (" + to_string(entFinder.RemovedCandidates()) + " removed)", 1);
		ConsoleHelper::PrintDebugInfo("[Entanglement Finder] Path Data:                 " + to_string(paths->size()) + " paths with " + to_string(totalActions) + " steps in total", 1);
	}

	return candidates;
}

PDDLInstance RandomWalkerReformulator::GenerateMacros(unordered_map<size_t, EntanglementOccurance> candidates, PDDLInstance* instance) {
	PDDLInstance newInstance(instance->domain, instance->problem);
	return newInstance;
}

SASPlan RandomWalkerReformulator::RebuildSASPlan(SASPlan* reformulatedSAS) {
	// Do Something and give a "corrected" SAS plan back
	SASPlan newPlan(reformulatedSAS->actions, reformulatedSAS->cost);
	return newPlan;
} 
