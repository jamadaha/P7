#include "EntanglementFinder.hh"

using namespace std;

vector<EntangledActionsSet> EntanglementFinder::FindEntangledCandidates(PDDLInstance* instance, vector<Path> paths) {
	vector<EntangledActionsSet> candidates;

	hash<string> hasher;

	int level = paths[0].steps.size();
	while (level > 1) {
		vector<pair<int, vector<PDDLActionInstance>>> currentValues;
		for (int i = 0; i < paths.size(); i++) {
			int counter = 0;
			bool addedAny = false;
			string pathStr;
			vector<PDDLActionInstance> currentSet;
			for (int j = 0; j < paths[i].steps.size(); j++) {
				auto aInstance = (paths[i].steps)[j];
				currentSet.push_back(aInstance);
				pathStr += aInstance.ToString(instance->problem, instance->domain);
				counter++;
				if (counter >= level) {
					currentValues.push_back(make_pair(hasher(pathStr), currentSet));
					addedAny = true;
				}
			}
			if (!addedAny)
				currentValues.push_back(make_pair(hasher(pathStr), currentSet));
		}

		for (int i = 0; i < currentValues.size(); i++) {
			for (int j = 0; j < currentValues.size(); j++) {
				if (currentValues[i].first == currentValues[j].first && i != j) {
					int hashValue = currentValues[i].first;
					bool isFound = false;
					for (int l = 0; l < candidates.size(); l++) {
						if (candidates[l].Hash == hashValue)
						{
							isFound = true;
							break;
						}
					}
					if (!isFound)
						candidates.push_back(EntangledActionsSet(hashValue, currentValues[i].second));
				}
			}
		}

		level = ceil((double)level / 2);
	}

	return candidates;
}