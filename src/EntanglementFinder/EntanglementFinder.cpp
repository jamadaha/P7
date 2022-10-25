#include "EntanglementFinder.hh"

using namespace std;

unordered_map<int, EntanglementOccurance> EntanglementFinder::FindEntangledCandidates(const vector<Path> paths) {
	unordered_map<int, EntanglementOccurance> candidates;

	if (paths.size() == 0)
		return candidates;
	int level = paths.at(0).steps.size();
	if (SearchCeiling != -1)
		level = SearchCeiling;
	if (SearchFloor < 2)
		throw exception();	
	if (LevelReductionFactor <= 1)
		throw exception();

	vector<vector<PDDLActionInstance>> currentValues;
	while (level >= SearchFloor) {
		GenerateActionSet(&currentValues, &paths, level);

		AddCandidatesIfThere(&candidates, currentValues);

		level = ceil((double)level / LevelReductionFactor);
	}

	RemoveIfBelowMinimum(&candidates);

	return unordered_map<int, EntanglementOccurance>(candidates);
}

void EntanglementFinder::GenerateActionSet(vector<vector<PDDLActionInstance>> *currentValues, const vector<Path>* paths, const int level) {
	currentValues->clear();
	for (int i = 0; i < paths->size(); i++) {
		for (int j = 0; j < paths->at(i).steps.size(); j += level) {
			vector<PDDLActionInstance> currentSet;
			currentSet.reserve(level);
			for (int l = j; l < j + level; l++) {
				if (l >= paths->at(i).steps.size())
					break;
				currentSet.push_back(((paths->at(i)).steps.at(l)));
			}
			currentValues->push_back(currentSet);
		}
	}
}

void EntanglementFinder::AddCandidatesIfThere(unordered_map<int, EntanglementOccurance>* candidates, vector<vector<PDDLActionInstance>> currentValues) {
	for (int i = 0; i < currentValues.size(); i++) {
		vector<PDDLActionInstance>* iValue = &currentValues.at(i);
		int key = hash<const vector<PDDLActionInstance>>{}(*iValue);
		bool containsThisKey = candidates->contains(key);
		EntanglementOccurance* currentOcc;
		const int iValueLength = iValue->size();
		for (int j = i + 1; j < currentValues.size(); j++) {
			if (IsEqual(iValue, (&currentValues.at(j)))) {
				if (containsThisKey) {
					currentOcc->Occurance++;
				}
				else {
					EntanglementOccurance newOcc(*iValue);
					candidates->emplace(make_pair(key, newOcc));
					containsThisKey = true;
					currentOcc = &candidates->at(key);
				}
			}
		}
	}
}

void EntanglementFinder::RemoveIfBelowMinimum(unordered_map<int, EntanglementOccurance>* candidates) {
	const auto removeIfLessThan = [&](pair<int, EntanglementOccurance> const& x) { return x.second.Occurance < MinimumOccurance; };
	std::erase_if(*candidates, removeIfLessThan);
}

bool EntanglementFinder::IsEqual(vector<PDDLActionInstance>* lhv, vector<PDDLActionInstance>* rhv) {
	if (lhv->size() != rhv->size())
		return false;
	for (int i = 0; i < lhv->size(); i++)
		if (lhv->at(i).GetHash() != rhv->at(i).GetHash())
			return false;
	return true;
}
