#include "EntanglementFinder.hh"

using namespace std;

unordered_map<size_t, EntanglementOccurance> EntanglementFinder::FindEntangledCandidates(vector<Path>* paths) {
	unordered_map<size_t, EntanglementOccurance> candidates;

	if (paths->size() == 0)
		return candidates;
	int level = 2;
	if (SearchCeiling != -1)
		level = SearchCeiling;
	else
	{
		for (int i = 0; i < paths->size(); i++)
			if (level < paths->at(i).steps.size())
				level = paths->at(i).steps.size();
	}
	if (level < 2)
		throw exception();
	if (SearchFloor < 2)
		throw exception();
	if (LevelReductionFactor <= 1)
		throw exception();

	s:vector<pair<size_t, vector<PDDLActionInstance*>>> currentValues;
	
	while (level >= SearchFloor) {
		CurrentLevel = level;
		GenerateActionSet(&currentValues, paths, level);

		AddCandidatesIfThere(&candidates, currentValues);

		level = ceil((double)level / LevelReductionFactor);
	}

	RemoveIfBelowMinimum(&candidates);

	return unordered_map<size_t, EntanglementOccurance>(candidates);
}

void EntanglementFinder::GenerateActionSet(vector<pair<size_t, vector<PDDLActionInstance*>>>* currentValues, vector<Path>* paths, const int level) {
	currentValues->clear();
	for (int i = 0; i < paths->size(); i++) {
		for (int j = 0; j < paths->at(i).steps.size(); j += level) {
			bool doAdd = true;
			vector<PDDLActionInstance*> currentSet;
			currentSet.reserve(level);
			for (int l = j; l < j + level; l++) {
				if (l >= paths->at(i).steps.size()) {
					if (l - j == 1)
						doAdd = false;
					break;
				}
				currentSet.push_back(&((paths->at(i)).steps.at(l)));
			}
			size_t key = hash<vector<PDDLActionInstance*>>{}(currentSet);
			if (doAdd)
				currentValues->push_back(make_pair(key, currentSet));
		}
	}
}

void EntanglementFinder::AddCandidatesIfThere(unordered_map<size_t, EntanglementOccurance>* candidates, vector<pair<size_t, vector<PDDLActionInstance*>>> currentValues) {
	const int currentValueSize = currentValues.size();
	if (OnNewLevel != nullptr)
		OnNewLevel(CurrentLevel, currentValueSize);

	for (int i = 0; i < currentValueSize; i++) {
		pair<size_t,vector<PDDLActionInstance*>>* iValue = &currentValues.at(i);
		bool containsThisKey = candidates->contains(iValue->first);
		if (containsThisKey)
			continue;
		EntanglementOccurance* currentOcc;
		for (int j = i + 1; j < currentValueSize; j++) {
			if (iValue->first == (&currentValues.at(j))->first) {
				if (containsThisKey) {
					currentOcc->Occurance++;
				}
				else {
					EntanglementOccurance newOcc(iValue->second, iValue->first);
					candidates->emplace(iValue->first, newOcc);
					containsThisKey = true;
					currentOcc = &candidates->at(iValue->first);
				}
			}
		}
		if (OnLevelIteration != nullptr)
			OnLevelIteration(i, currentValueSize);
	}
	if (OnLevelEnd != nullptr)
		OnLevelEnd();
}

void EntanglementFinder::RemoveIfBelowMinimum(unordered_map<size_t, EntanglementOccurance>* candidates) {
	const auto removeIfLessThan = [&](pair<size_t, EntanglementOccurance> const& x) { return x.second.Occurance < MinimumOccurance; };
	std::erase_if(*candidates, removeIfLessThan);
}
