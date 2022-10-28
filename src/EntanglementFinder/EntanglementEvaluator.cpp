#include "EntanglementEvaluator.hh"

using namespace std;

vector<EntanglementOccurance> EntanglementEvaluator::EvaluateAndSanitizeCandidates(unordered_map<size_t, EntanglementOccurance> candidates) {
	vector<EntanglementOccurance> sanitizedCandidates;
	int preCount = candidates.size();

	RemoveIfBelowMinimum(&candidates);

	SetQualityByLength(&candidates);
	SetQualityByOccurance(&candidates);

	_RemovedCandidates = preCount - candidates.size();

	return SortCandidates(&candidates);
}


void EntanglementEvaluator::RemoveIfBelowMinimum(unordered_map<size_t, EntanglementOccurance>* candidates) {
	const auto removeIfLessThan = [&](pair<size_t, EntanglementOccurance> const& x) { return x.second.Occurance < Data.MinimumOccurance; };
	std::erase_if(*candidates, removeIfLessThan);
}

void EntanglementEvaluator::SetQualityByLength(unordered_map<size_t, EntanglementOccurance>* candidates) {
	int maxLength = 0;
	for (auto itt = candidates->begin(); itt != candidates->end(); itt++) {
		if ((*itt).second.Chain.size() > maxLength)
			maxLength = (*itt).second.Chain.size();
	}
	for (auto itt = candidates->begin(); itt != candidates->end(); itt++) {
		(*itt).second.Quality *= (double)maxLength / (double)(*itt).second.Chain.size();
	}
}

void EntanglementEvaluator::SetQualityByOccurance(unordered_map<size_t, EntanglementOccurance>* candidates) {
	int maxOccurance = 0;
	for (auto itt = candidates->begin(); itt != candidates->end(); itt++) {
		if ((*itt).second.Occurance > maxOccurance)
			maxOccurance = (*itt).second.Occurance;
	}
	for (auto itt = candidates->begin(); itt != candidates->end(); itt++) {
		(*itt).second.Quality *= (double)(*itt).second.Occurance / (double)maxOccurance;
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
