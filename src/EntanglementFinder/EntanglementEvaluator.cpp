#include "EntanglementEvaluator.hh"

using namespace std;

vector<MacroCandidate> EntanglementEvaluator::EvaluateAndSanitizeCandidates(unordered_map<size_t, EntanglementOccurance> candidates) {
	// Setup default modifiers
	SetModifiersIfNotSet();

	auto macroCandidates = CombineCandidates(&candidates);
	_CombinedCandidates = macroCandidates.size();
	int preCount = macroCandidates.size();

	// Modify remaining candidates Quality
	SetQualityByLength(&macroCandidates);
	SetQualityByOccurance(&macroCandidates);

	// Sanitize candidates
	RemoveMinimumQuality(&macroCandidates);

	_RemovedCandidates = preCount - macroCandidates.size();

	auto sanitizedCandidates = SortCandidates(&macroCandidates);
	if (sanitizedCandidates.size() > Data.MaxCandidates) {
		sanitizedCandidates.erase(sanitizedCandidates.begin() + Data.MaxCandidates, sanitizedCandidates.end());
	}
	return sanitizedCandidates;
}

void EntanglementEvaluator::SetModifiersIfNotSet() {
	if (LengthModifier == nullptr)
		LengthModifier = EntanglementEvaluatorModifiers::LengthModifiers::Default;
	if (OccuranceModifier == nullptr)
		OccuranceModifier = EntanglementEvaluatorModifiers::OccuranceModifiers::Default;
}

void EntanglementEvaluator::RemoveMinimumQuality(vector<MacroCandidate>* candidates) {
	const auto removeIfLessThan = [&](MacroCandidate const& x) { return x.Quality < Data.MinimumQualityPercent; };
	std::erase_if(*candidates, removeIfLessThan);
}

void EntanglementEvaluator::SetQualityByLength(vector<MacroCandidate>* candidates) {
	double maxLength = 0;
	for (auto itt = candidates->begin(); itt != candidates->end(); itt++) {
		if ((*itt).Entanglements.at(0).size() > maxLength)
			maxLength = (*itt).Entanglements.at(0).size();
	}
	for (auto itt = candidates->begin(); itt != candidates->end(); itt++) {
		double newQuality = (*itt).Quality * LengthModifier((*itt).Entanglements.at(0).size(), maxLength);
		(*itt).Quality *= min((double)1, newQuality);
	}
}

void EntanglementEvaluator::SetQualityByOccurance(vector<MacroCandidate>* candidates) {
	double maxOccurance = 0;
	for (auto itt = candidates->begin(); itt != candidates->end(); itt++) {
		if ((*itt).Occurance > maxOccurance)
			maxOccurance = (*itt).Occurance;
	}
	for (auto itt = candidates->begin(); itt != candidates->end(); itt++) {
		double newQuality = (*itt).Quality * OccuranceModifier((*itt).Occurance, maxOccurance);
		(*itt).Quality *= min((double)1, newQuality);
	}
}

vector<MacroCandidate> EntanglementEvaluator::CombineCandidates(unordered_map<size_t, EntanglementOccurance>* candidates) {
	vector<MacroCandidate> combinedCandidates;

	for (auto i = candidates->begin(); i != candidates->end(); i++) {
		bool foundAny = false;
		for (auto j = combinedCandidates.begin(); j != combinedCandidates.end(); j++) {
			bool isSame = true;
			if (i->second.Chain.size() != j->Entanglements.at(0).size())
				continue;
			for (int k = 0; k < i->second.Chain.size(); k++) {
				if (i->second.Chain.at(k)->action->name != j->Entanglements.at(0).at(k)->action->name) {
					isSame = false;
					break;
				}
			}
			if (isSame) {
				j->Entanglements.push_back(i->second.Chain);
				j->BetweenDifferentPaths += i->second.BetweenDifferentPaths;
				j->Occurance += i->second.Occurance;
				foundAny = true;
			}
		}
		if (!foundAny)
			combinedCandidates.push_back(MacroCandidate(vector<vector<PDDLActionInstance*>> { i->second.Chain }, i->second.Occurance, i->second.BetweenDifferentPaths));
	}

	return combinedCandidates;
}

vector<MacroCandidate> EntanglementEvaluator::SortCandidates(vector<MacroCandidate>* candidates) {
	vector<MacroCandidate> sortedCandidates;
	for (auto itt = candidates->begin(); itt != candidates->end(); itt++) {
		int index = 0;
		for (int i = 0; i < sortedCandidates.size(); i++) {
			if ((*itt).Quality > sortedCandidates.at(i).Quality)
				break;
			index++;
		}
		auto realIndex = sortedCandidates.begin() + index;
		sortedCandidates.insert(realIndex, (*itt));
	}
	return sortedCandidates;
}
