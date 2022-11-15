#include "EntanglementFinder.hh"

using namespace std;

int EntanglementFinder::GetInitialLevelIfValid(vector<Path>* paths) {
	int level = 2;
	if (Data.SearchCeiling != -1)
		level = Data.SearchCeiling;
	else
	{
		for (int i = 0; i < paths->size(); i++)
			if (level < paths->at(i).steps.size())
				level = paths->at(i).steps.size();
	}
	if (level < 2)
		throw exception();
	if (Data.SearchFloor < 2)
		throw exception();
	if (Data.LevelReductionType == RunData::LevelReductionTypes::None)
		throw exception();
	if (Data.LevelReductionType == RunData::LevelReductionTypes::Division)
		if (Data.LevelReductionFactor <= 1)
			throw exception();
	if (Data.LevelReductionType == RunData::LevelReductionTypes::Subtraction)
		if (Data.LevelReductionFactor < 1)
			throw exception();
	if (Data.TimeLimitMs != -1)
		_HasTimeLimit = true;

	return level;
}

unordered_map<size_t, EntanglementOccurance> EntanglementFinder::FindEntangledCandidates(vector<Path>* paths) {
	unordered_map<size_t, EntanglementOccurance> candidates;

	if (paths->size() == 0)
		return candidates;

	int level = GetInitialLevelIfValid(paths);

	vector<pair<pair<size_t, int>, vector<PDDLActionInstance*>>> currentValues;
	
	_TotalLevels = 0;
	_TotalComparisons = 0;

	_StartTime = chrono::steady_clock::now();
	while (level >= Data.SearchFloor) {
		_TotalLevels++;
		_CurrentLevel = level;
		GenerateActionSet(&currentValues, paths, level);

		AddCandidatesIfThere(&candidates, &currentValues);

		level = ReduceLevel(level);

		if (_IsTimeLimitReached)
			break;
	}

	return unordered_map<size_t, EntanglementOccurance>(candidates);
}

int EntanglementFinder::ReduceLevel(int level) {
	int newLevel = level;
	if (Data.LevelReductionType == RunData::LevelReductionTypes::Division)
		newLevel = ceil((double)level / Data.LevelReductionFactor);
	else if (Data.LevelReductionType == RunData::LevelReductionTypes::Subtraction)
		newLevel -= Data.LevelReductionFactor;
	if (level == newLevel)
		throw exception();
	return newLevel;
}

void EntanglementFinder::GenerateActionSet(vector<pair<pair<size_t, int>, vector<PDDLActionInstance*>>>* currentValues, vector<Path>* paths, const int level) {
	currentValues->clear();
	const int pathsSize = paths->size();
	for (int i = 0; i < pathsSize; i++) {
		Path* path = &paths->at(i);
		const int pathSize = path->steps.size();
		for (int j = 0; j < pathSize; j += level) {
			bool doAdd = true;
			vector<PDDLActionInstance*> currentSet;
			currentSet.reserve(level);
			for (int l = j; l < j + level; l++) {
				if (l >= pathSize) {
					if (l - j == 1)
						doAdd = false;
					break;
				}
				currentSet.push_back(&(path->steps.at(l)));
			}
			if (doAdd) {
				size_t key = hash<vector<PDDLActionInstance*>>{}(currentSet);
				currentValues->push_back(make_pair(make_pair(key, i), currentSet));
			}
		}
	}
}

void EntanglementFinder::AddCandidatesIfThere(unordered_map<size_t, EntanglementOccurance>* candidates, vector<pair<pair<size_t, int>, vector<PDDLActionInstance*>>>* currentValues) {
	const int currentValueSize = currentValues->size();
	if (OnNewLevel != nullptr)
		OnNewLevel(_CurrentLevel, currentValueSize);

	for (int i = 0; i < currentValueSize; i++) {
		// Check if this value have already been found
		pair<pair<size_t, int>,vector<PDDLActionInstance*>>* iValue = &currentValues->at(i);
		bool containsThisKey = candidates->contains(iValue->first.first);
		if (containsThisKey)
			continue;
		EntanglementOccurance* currentOcc;
		for (int j = i + 1; j < currentValueSize; j++) {
			_TotalComparisons++;
			if (iValue->first.first == (&currentValues->at(j))->first.first) {
				if (containsThisKey) {
					// Increment occurance
					currentOcc->Occurance++;
					currentOcc->BetweenDifferentPaths += iValue->first.second != (&currentValues->at(j))->first.second;
				}
				else {
					// Add new candidate
					EntanglementOccurance newOcc(iValue->second, iValue->first.first, 1 + (iValue->first.second != (&currentValues->at(j))->first.second));
					candidates->emplace(iValue->first.first, newOcc);
					containsThisKey = true;
					currentOcc = &candidates->at(iValue->first.first);
				}
			}
			if (IsOverTimeLimit())
				break;
		}
		if (OnLevelIteration != nullptr)
			OnLevelIteration(i, currentValueSize);
		if (IsOverTimeLimit())
			break;
	}
	if (OnLevelEnd != nullptr)
		OnLevelEnd();
}

bool EntanglementFinder::IsOverTimeLimit() {
	if (_HasTimeLimit) {
		if (_IsTimeLimitReached)
			return true;
		auto currentTime = chrono::steady_clock::now();
		auto ellapsed = chrono::duration_cast<chrono::milliseconds>(currentTime - _StartTime).count();
		if (ellapsed > Data.TimeLimitMs) {
			if (OnTimeLimitReached != nullptr)
				OnTimeLimitReached();
			_IsTimeLimitReached = true;
			return true;
		}
	}
	return false;
}