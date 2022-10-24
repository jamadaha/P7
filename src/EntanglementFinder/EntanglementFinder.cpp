#include "EntanglementFinder.hh"

using namespace std;

unordered_set<vector<PDDLActionInstance>> EntanglementFinder::FindEntangledCandidates(vector<Path> paths) {
	unordered_set<vector<PDDLActionInstance>> candidates;

	int level = paths[0].steps.size();
	if (SearchCeiling != -1)
		level = SearchCeiling;
	if (SearchFloor < 2)
		throw exception();	

	while (level >= SearchFloor) {
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

		for (int i = 0; i < currentValues.size(); i++) {
			for (int j = 0; j < currentValues.size(); j++) {
				if (currentValues[i] == currentValues[j] && i != j) {
					candidates.emplace(currentValues[i]);
				}
			}
		}

		level = ceil((double)level / 2);
	}

	return candidates;
}