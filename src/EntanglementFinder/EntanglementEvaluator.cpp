#include "EntanglementEvaluator.hh"

using namespace std;

void EntanglementEvaluator::EvaluateAndSanitizeCandidates(unordered_map<size_t, EntanglementOccurance>* candidates) {
	int preCount = candidates->size();

	RemoveIfBelowMinimum(candidates);

	_RemovedCandidates = preCount - candidates->size();
}


void EntanglementEvaluator::RemoveIfBelowMinimum(unordered_map<size_t, EntanglementOccurance>* candidates) {
	const auto removeIfLessThan = [&](pair<size_t, EntanglementOccurance> const& x) { return x.second.Occurance < Data.MinimumOccurance; };
	std::erase_if(*candidates, removeIfLessThan);
}
