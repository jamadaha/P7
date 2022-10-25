#include "EntanglementFinder.hh"

using namespace std;

unordered_map<size_t, EntanglementOccurance> EntanglementFinder::FindEntangledCandidates(vector<Path> paths) {
	unordered_map<size_t, EntanglementOccurance> candidates;

	if (paths.size() == 0)
		return candidates;
	int level = 2;
	if (SearchCeiling != -1)
		level = SearchCeiling;
	else
	{
		for (int i = 0; i < paths.size(); i++)
			if (level < paths.at(i).steps.size())
				level = paths.at(i).steps.size();
	}
	if (level < 2)
		throw exception();
	if (SearchFloor < 2)
		throw exception();
	if (LevelReductionFactor <= 1)
		throw exception();

	int iterations = 0;
	int testLevel = level;
	while (testLevel >= SearchFloor) {
		testLevel = ceil((double)testLevel / LevelReductionFactor);
		iterations++;
	}

	vector<vector<PDDLActionInstance>> currentValues;
	ProgressBarHelper bar(iterations, "Finding Entanglements");
	while (level >= SearchFloor) {
		GenerateActionSet(&currentValues, &paths, level);

		AddCandidatesIfThere(&candidates, currentValues);

		level = ceil((double)level / LevelReductionFactor);
		bar.Update();
	}
	bar.End();

	RemoveIfBelowMinimum(&candidates);

	return unordered_map<size_t, EntanglementOccurance>(candidates);
}

void EntanglementFinder::GenerateActionSet(vector<vector<PDDLActionInstance>> *currentValues, const vector<Path>* paths, const int level) {
	currentValues->clear();
	for (int i = 0; i < paths->size(); i++) {
		for (int j = 0; j < paths->at(i).steps.size(); j += level) {
			bool doAdd = true;
			vector<PDDLActionInstance> currentSet;
			currentSet.reserve(level);
			for (int l = j; l < j + level; l++) {
				if (l >= paths->at(i).steps.size()) {
					if (l - j == 1)
						doAdd = false;
					break;
				}
				currentSet.push_back(((paths->at(i)).steps.at(l)));
			}
			if (doAdd)
				currentValues->push_back(currentSet);
		}
	}
}

void EntanglementFinder::AddCandidatesIfThere(unordered_map<size_t, EntanglementOccurance>* candidates, vector<vector<PDDLActionInstance>> currentValues) {
	const int currentValueSize = currentValues.size();
	for (int i = 0; i < currentValueSize; i++) {
		vector<PDDLActionInstance>* iValue = &currentValues.at(i);
		size_t key = hash<const vector<PDDLActionInstance>>{}(*iValue);
		bool containsThisKey = candidates->contains(key);
		if (containsThisKey)
			continue;
		EntanglementOccurance* currentOcc;
		for (int j = i + 1; j < currentValueSize; j++) {
			if (IsEqual(iValue, (&currentValues.at(j)))) {
				if (containsThisKey) {
					currentOcc->Occurance++;
				}
				else {
					EntanglementOccurance newOcc(*iValue, key);
					candidates->emplace(key, newOcc);
					containsThisKey = true;
					currentOcc = &candidates->at(key);
				}
			}
		}
	}
}

void EntanglementFinder::RemoveIfBelowMinimum(unordered_map<size_t, EntanglementOccurance>* candidates) {
	const auto removeIfLessThan = [&](pair<size_t, EntanglementOccurance> const& x) { return x.second.Occurance < MinimumOccurance; };
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
