#include "Evaluator.hh"

using namespace std;
using namespace JointPaths;

vector<JointPath> Evaluator::EvaluateAndSanitizeCandidates(unordered_map<size_t, JointPath> candidates) {
	// Setup default modifiers
	SetModifiersIfNotSet();

	// Convert to vector for easier access
	vector<JointPath> convertedCandidates = ConvertToVector(&candidates);
	int preCount = convertedCandidates.size();

	// Modify remaining candidates Quality
	SetQualityByLength(&convertedCandidates);
	SetQualityByOccurance(&convertedCandidates);

	// Sanitize candidates
	RemoveMinimumQuality(&convertedCandidates);

	_RemovedCandidates = preCount - convertedCandidates.size();

	// Sort the candidates
	vector<JointPath> sortedCandidates = SortCandidates(&convertedCandidates);

	// Remove candidates if there are too many
	RemoveIfTooMany(&sortedCandidates);

	return sortedCandidates;
}

void Evaluator::SetModifiersIfNotSet() {
	if (LengthModifier == nullptr)
		LengthModifier = EvaluationModifiers::LengthModifiers::Default;
	if (OccuranceModifier == nullptr)
		OccuranceModifier = EvaluationModifiers::OccuranceModifiers::Default;
}

void Evaluator::RemoveMinimumQuality(vector<JointPath>* candidates) {
	std::erase_if(*candidates, RemoveIfLessThanFunc);
}

void Evaluator::RemoveIfTooMany(vector<JointPath>* candidates) {
	if (candidates->size() > Data.MaxCandidates) {
		candidates->erase(candidates->begin() + Data.MaxCandidates, candidates->end());
	}
}

void Evaluator::SetQualityByLength(vector<JointPath>* candidates) {
	double maxLength = 0;
	for (auto candidate = candidates->begin(); candidate != candidates->end(); candidate++) {
		if (candidate->ChainSize > maxLength)
			maxLength = candidate->ChainSize;
	}
	for (auto candidate = candidates->begin(); candidate != candidates->end(); candidate++) {
		double newQuality = candidate->Quality * LengthModifier(candidate->ChainSize, maxLength);
		candidate->Quality = min((double)1, newQuality);
	}
}

void Evaluator::SetQualityByOccurance(vector<JointPath>* candidates) {
	double maxOccurance = 0;
	for (auto candidate = candidates->begin(); candidate != candidates->end(); candidate++) {
		if (candidate->Occurance > maxOccurance)
			maxOccurance = candidate->Occurance;
	}
	for (auto candidate = candidates->begin(); candidate != candidates->end(); candidate++) {
		double newQuality = candidate->Quality * OccuranceModifier(candidate->Occurance, maxOccurance);
		candidate->Quality = min((double)1, newQuality);
	}
}

vector<JointPath> Evaluator::ConvertToVector(unordered_map<size_t, JointPath>* candidates) {
	vector<JointPath> vetorCandidates;
	vetorCandidates.reserve(candidates->size());
	for (auto candidate = candidates->begin(); candidate != candidates->end(); candidate++) {
		vetorCandidates.push_back(candidate->second);
	}
	return vetorCandidates;
}

vector<JointPath> Evaluator::SortCandidates(vector<JointPath>* candidates) {
	vector<JointPath> sortedCandidates;
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
