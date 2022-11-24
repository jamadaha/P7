#include "Finder.hh"

using namespace std;
using namespace JointPaths;

int Finder::GetInitialLevelIfValid(vector<Path>* paths) {
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

	return level;
}

unordered_map<size_t, EntanglementOccurance> Finder::FindEntangledCandidates(vector<Path>* paths) {
	unordered_map<size_t, EntanglementOccurance> candidates;

	if (paths->size() == 0)
		return candidates;

	int level = GetInitialLevelIfValid(paths);

	int totalSteps = 0;
	for (auto path = paths->begin(); path != paths->end(); path++)
		totalSteps += path->steps.size();

	vector<pair<size_t, vector<PDDLActionInstance*>>> currentValues;
	currentValues.reserve(totalSteps / Data.SearchFloor);

	_TotalLevels = 0;
	_TotalComparisons = 0;

	while (level >= Data.SearchFloor) {
		_TotalLevels++;
		_CurrentLevel = level;

		currentValues.clear();
		GenerateActionSet(&currentValues, paths, level);

		AddCandidatesIfThere(&candidates, &currentValues);

		level = ReduceLevel(level);

		if (_IsTimeLimitReached)
			break;
	}

	return candidates;
	//return unordered_map<size_t, EntanglementOccurance>(candidates);
}

int Finder::ReduceLevel(int level) {
	int newLevel = level;
	if (Data.LevelReductionType == RunData::LevelReductionTypes::Division)
		newLevel = ceil((double)level / Data.LevelReductionFactor);
	else if (Data.LevelReductionType == RunData::LevelReductionTypes::Subtraction)
		newLevel -= Data.LevelReductionFactor;
	if (level == newLevel)
		throw exception();
	return newLevel;
}

void Finder::GenerateActionSet(vector<pair<size_t, vector<PDDLActionInstance*>>>* currentValues, vector<Path>* paths, const int level) {
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
				currentValues->push_back(make_pair(key, currentSet));
			}
		}
	}
}

void Finder::AddCandidatesIfThere(unordered_map<size_t, EntanglementOccurance>* candidates, const vector<pair<size_t, vector<PDDLActionInstance*>>>* currentValues) {
	const int currentValueSize = currentValues->size();
	if (OnNewLevel != nullptr)
		OnNewLevel(_CurrentLevel, currentValueSize);

	for (int i = 0; i < currentValueSize; i++) {
		// Check if this value have already been found
		pair<size_t,vector<PDDLActionInstance*>> iValue = currentValues->at(i);
		bool containsThisKey = candidates->contains(iValue.first);
		if (containsThisKey)
			continue;
		EntanglementOccurance* currentOcc;
		for (int j = i + 1; j < currentValueSize; j++) {
			_TotalComparisons++;
			if (iValue.first == currentValues->at(j).first) {
				if (containsThisKey) {
					// Increment occurance
					currentOcc->Occurance++;
				}
				else {
					// Add new candidate
					EntanglementOccurance newOcc(iValue.second, iValue.first);
					candidates->emplace(iValue.first, newOcc);
					containsThisKey = true;
					currentOcc = &candidates->at(iValue.first);
				}
			}
		}
		if (OnLevelIteration != nullptr)
			OnLevelIteration(i, currentValueSize);
		if (IsOverTimeLimit())
			break;
	}
	if (OnLevelEnd != nullptr)
		OnLevelEnd();
}

bool Finder::IsOverTimeLimit() {
	if (_HasTimeLimit) {
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