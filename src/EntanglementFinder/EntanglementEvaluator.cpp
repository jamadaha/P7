#include "EntanglementEvaluator.hh"

using namespace std;

vector<EntanglementOccurance> EntanglementEvaluator::EvaluateAndSanitizeCandidates(unordered_map<size_t, EntanglementOccurance> candidates) {
	vector<EntanglementOccurance> sanitizedCandidates;
	int preCount = candidates.size();

	// Setup default modifiers
	SetModifiersIfNotSet();

	// Sanitize candidates
	FindMinimumOccurances(&candidates);
	RemoveMinimumOccurances(&candidates);
	RemoveMinimumCrossOccurances(&candidates);

	// Modify remaining candidates Quality
	SetQualityByLength(&candidates);
	SetQualityByOccurance(&candidates);

	_RemovedCandidates = preCount - candidates.size();

	return SortCandidates(&candidates);
}

void EntanglementEvaluator::SetModifiersIfNotSet() {
	if (LengthModifier == nullptr)
		LengthModifier = EntanglementEvaluatorModifiers::LengthModifiers::Default;
	if (OccuranceModifier == nullptr)
		OccuranceModifier = EntanglementEvaluatorModifiers::OccuranceModifiers::Default;
}

void EntanglementEvaluator::FindMinimumOccurances(unordered_map<size_t, EntanglementOccurance>* candidates) {
	if (Data.MinimumCrossOccurancePercent <= 0)
		invalid_argument("Minimum cross occurance is too low!");
	if (Data.MinimumCrossOccurancePercent > 1)
		invalid_argument("Minimum cross occurance is too high!");
	if (Data.MinimumOccurancePercent <= 0)
		invalid_argument("Minimum occurance is too low!");
	if (Data.MinimumOccurancePercent > 1)
		invalid_argument("Minimum occurance is too high!");

	int largestOccurances = 0;
	int largestCrossOccurances = 0;
	for (auto itt = candidates->begin(); itt != candidates->end(); itt++) {
		if ((*itt).second.Occurance > largestOccurances)
			largestOccurances = (*itt).second.Occurance;
		if ((*itt).second.BetweenDifferentPaths > largestCrossOccurances)
			largestCrossOccurances = (*itt).second.BetweenDifferentPaths;
	}

	_MinimumOccurance = largestOccurances * Data.MinimumOccurancePercent;
	_MinimumCrossOccurance = largestCrossOccurances * Data.MinimumCrossOccurancePercent;
}

void EntanglementEvaluator::RemoveMinimumOccurances(unordered_map<size_t, EntanglementOccurance>* candidates) {
	const auto removeIfLessThan = [&](pair<size_t, EntanglementOccurance> const& x) { return x.second.Occurance < _MinimumOccurance; };
	std::erase_if(*candidates, removeIfLessThan);
}

void EntanglementEvaluator::RemoveMinimumCrossOccurances(unordered_map<size_t, EntanglementOccurance>* candidates) {
	const auto removeIfLessThan = [&](pair<size_t, EntanglementOccurance> const& x) { return x.second.BetweenDifferentPaths < _MinimumCrossOccurance; };
	std::erase_if(*candidates, removeIfLessThan);
}

void EntanglementEvaluator::SetQualityByLength(unordered_map<size_t, EntanglementOccurance>* candidates) {
	double maxLength = 0;
	for (auto itt = candidates->begin(); itt != candidates->end(); itt++) {
		if ((*itt).second.Chain.size() > maxLength)
			maxLength = (*itt).second.Chain.size();
	}
	for (auto itt = candidates->begin(); itt != candidates->end(); itt++) {
		(*itt).second.Quality *= LengthModifier((*itt).second.Chain.size(), maxLength);
	}
}

void EntanglementEvaluator::SetQualityByOccurance(unordered_map<size_t, EntanglementOccurance>* candidates) {
	double maxOccurance = 0;
	for (auto itt = candidates->begin(); itt != candidates->end(); itt++) {
		if ((*itt).second.Occurance > maxOccurance)
			maxOccurance = (*itt).second.Occurance;
	}
	for (auto itt = candidates->begin(); itt != candidates->end(); itt++) {
		(*itt).second.Quality *= OccuranceModifier((*itt).second.Occurance, maxOccurance);
	}
}

vector<EntanglementOccurance> EntanglementEvaluator::SortCandidates(unordered_map<size_t, EntanglementOccurance>* candidates) {
	vector<EntanglementOccurance> sanitizedCandidates;
	for (auto itt = candidates->begin(); itt != candidates->end(); itt++) {
		int index = 0;
		for (int i = 0; i < sanitizedCandidates.size(); i++) {
			if ((*itt).second.Quality > sanitizedCandidates.at(i).Quality)
				break;
			index++;
		}
		auto realIndex = sanitizedCandidates.begin() + index;
		sanitizedCandidates.insert(realIndex, (*itt).second);
	}
	return sanitizedCandidates;
}
