#include "EntanglementFinder.hh"

using namespace std;

unordered_set<EntanglementOccurance> EntanglementFinder::FindEntangledCandidates(vector<Path> paths) {
	unordered_set<EntanglementOccurance> candidates;

	int level = paths[0].steps.size();
	if (SearchCeiling != -1)
		level = SearchCeiling;
	if (SearchFloor < 2)
		throw exception();	
	if (LevelReductionFactor <= 1)
		throw exception();

	while (level >= SearchFloor) {
		vector<vector<PDDLActionInstance>> currentValues = GenerateActionSet(paths, level);

		AddCandidatesIfThere(&candidates, currentValues);

		level = ceil((double)level / 2);
	}

	return candidates;
}

vector<vector<PDDLActionInstance>> EntanglementFinder::GenerateActionSet(vector<Path> paths, int level) {
	vector<vector<PDDLActionInstance>> currentValues;
	for (int i = 0; i < paths.size(); i++) {
		int counter = 0;
		vector<PDDLActionInstance> currentSet;
		for (int j = 0; j < paths[i].steps.size(); j++) {
			auto aInstance = (paths[i].steps)[j];
			currentSet.push_back(aInstance);
			counter++;
			if (counter >= level) {
				currentValues.push_back(currentSet);
				currentSet.clear();
				counter = 0;
			}
		}
		if (currentSet.size() != 0)
			currentValues.push_back(currentSet);
	}
	return currentValues;
}

void EntanglementFinder::AddCandidatesIfThere(unordered_set<EntanglementOccurance>* candidates, std::vector<std::vector<PDDLActionInstance>> currentValues) {
	for (int i = 0; i < currentValues.size(); i++) {
		for (int j = i; j < currentValues.size(); j++) {
			if (currentValues[i] == currentValues[j] && i != j) {
				EntanglementOccurance newOcc(currentValues[i]);
				auto potentialItem = candidates->find(newOcc);
				if (potentialItem != candidates->end()) {
					auto existingItem = &(*potentialItem);
					existingItem->Occurance++;
				}
				else
					candidates->emplace(newOcc);
			}
		}
	}
}
