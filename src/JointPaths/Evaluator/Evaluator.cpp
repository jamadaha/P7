#include "Evaluator.hh"

using namespace std;
using namespace JointPaths;

vector<EntanglementOccurance> Evaluator::EvaluateAndSanitizeCandidates(unordered_map<size_t, EntanglementOccurance> candidates) {
	// Setup default modifiers
	SetModifiersIfNotSet();

	// Convert to vector for easier access
	vector<EntanglementOccurance> convertedCandidates = ConvertToVector(&candidates);
	int preCount = convertedCandidates.size();

	// Modify remaining candidates Quality
	SetQualityByLength(&convertedCandidates);
	SetQualityByOccurance(&convertedCandidates);

	// Sanitize candidates
	RemoveMinimumQuality(&convertedCandidates);

	_RemovedCandidates = preCount - convertedCandidates.size();

	// Sort the candidates
	vector<EntanglementOccurance> sortedCandidates = SortCandidates(&convertedCandidates);

	// Remove candidates if there are too many
	RemoveIfTooMany(&sortedCandidates);

	return sortedCandidates;
}

void Evaluator::SetModifiersIfNotSet() {
	if (LengthModifier == nullptr)
		LengthModifier = EntanglementEvaluatorModifiers::LengthModifiers::Default;
	if (OccuranceModifier == nullptr)
		OccuranceModifier = EntanglementEvaluatorModifiers::OccuranceModifiers::Default;
}

void Evaluator::RemoveMinimumQuality(vector<EntanglementOccurance>* candidates) {
	const auto removeIfLessThan = [&](EntanglementOccurance const& candidate) { return candidate.Quality < Data.MinimumQualityPercent; };
	std::erase_if(*candidates, removeIfLessThan);
}

void Evaluator::RemoveIfTooMany(vector<EntanglementOccurance>* candidates) {
	if (candidates->size() > Data.MaxCandidates) {
		candidates->erase(candidates->begin() + Data.MaxCandidates, candidates->end());
	}
}

void Evaluator::SetQualityByLength(vector<EntanglementOccurance>* candidates) {
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

void Evaluator::SetQualityByOccurance(vector<EntanglementOccurance>* candidates) {
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

vector<EntanglementOccurance> Evaluator::ConvertToVector(unordered_map<size_t, EntanglementOccurance>* candidates) {
	vector<EntanglementOccurance> vetorCandidates;
	vetorCandidates.reserve(candidates->size());
	for (auto candidate = candidates->begin(); candidate != candidates->end(); candidate++) {
		vetorCandidates.push_back(candidate->second);
	}
	return vetorCandidates;
}

vector<EntanglementOccurance> Evaluator::SortCandidates(vector<EntanglementOccurance>* candidates) {
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
