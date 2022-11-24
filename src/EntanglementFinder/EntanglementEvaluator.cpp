#include "EntanglementEvaluator.hh"

using namespace std;

vector<EntanglementOccurance> EntanglementEvaluator::EvaluateAndSanitizeCandidates(unordered_map<size_t, EntanglementOccurance> candidates) {
	// Setup default modifiers
	SetModifiersIfNotSet();

	vector<EntanglementOccurance> convertedCandidates = ConvertToVector(&candidates);
	int preCount = convertedCandidates.size();

	// Modify remaining candidates Quality
	SetQualityByLength(&convertedCandidates);
	SetQualityByOccurance(&convertedCandidates);

	// Sanitize candidates
	RemoveMinimumQuality(&convertedCandidates);

	_RemovedCandidates = preCount - convertedCandidates.size();

	vector<EntanglementOccurance> sortedCandidates = SortCandidates(&convertedCandidates);
	if (sortedCandidates.size() > Data.MaxCandidates) {
		sortedCandidates.erase(sortedCandidates.begin() + Data.MaxCandidates, sortedCandidates.end());
	}
	return sortedCandidates;
}

void EntanglementEvaluator::SetModifiersIfNotSet() {
	if (LengthModifier == nullptr)
		LengthModifier = EntanglementEvaluatorModifiers::LengthModifiers::Default;
	if (OccuranceModifier == nullptr)
		OccuranceModifier = EntanglementEvaluatorModifiers::OccuranceModifiers::Default;
}

void EntanglementEvaluator::RemoveMinimumQuality(vector<EntanglementOccurance>* candidates) {
	const auto removeIfLessThan = [&](EntanglementOccurance const& candidate) { return candidate.Quality < Data.MinimumQualityPercent; };
	std::erase_if(*candidates, removeIfLessThan);
}

void EntanglementEvaluator::SetQualityByLength(vector<EntanglementOccurance>* candidates) {
	double maxLength = 0;
	for (auto candidate = candidates->begin(); candidate != candidates->end(); candidate++) {
		if (candidate->Chain.size() > maxLength)
			maxLength = candidate->Chain.size();
	}
	for (auto candidate = candidates->begin(); candidate != candidates->end(); candidate++) {
		double newQuality = candidate->Quality * LengthModifier(candidate->Chain.size(), maxLength);
		candidate->Quality *= min((double)1, newQuality);
	}
}

void EntanglementEvaluator::SetQualityByOccurance(vector<EntanglementOccurance>* candidates) {
	double maxOccurance = 0;
	for (auto candidate = candidates->begin(); candidate != candidates->end(); candidate++) {
		if (candidate->Occurance > maxOccurance)
			maxOccurance = candidate->Occurance;
	}
	for (auto candidate = candidates->begin(); candidate != candidates->end(); candidate++) {
		double newQuality = candidate->Quality * OccuranceModifier(candidate->Occurance, maxOccurance);
		candidate->Quality *= min((double)1, newQuality);
	}
}

vector<EntanglementOccurance> EntanglementEvaluator::ConvertToVector(unordered_map<size_t, EntanglementOccurance>* candidates) {
	vector<EntanglementOccurance> vetorCandidates;
	vetorCandidates.reserve(candidates->size());
	for (auto candidate = candidates->begin(); candidate != candidates->end(); candidate++) {
		vetorCandidates.push_back(candidate->second);
	}
	return vetorCandidates;
}

vector<EntanglementOccurance> EntanglementEvaluator::SortCandidates(vector<EntanglementOccurance>* candidates) {
	vector<EntanglementOccurance> sortedCandidates;
	for (auto candidate = candidates->begin(); candidate != candidates->end(); candidate++) {
		int index = 0;
		for (int i = 0; i < sortedCandidates.size(); i++) {
			if (candidate->Quality > sortedCandidates.at(i).Quality)
				break;
			index++;
		}
		sortedCandidates.insert(sortedCandidates.begin() + index, (*candidate));
	}
	return sortedCandidates;
}
