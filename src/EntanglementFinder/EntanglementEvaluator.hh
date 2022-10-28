#ifndef EntanglementEvaluator_HH
#define EntanglementEvaluator_HH

#include <string>
#include <vector>
#include <math.h>
#include <unordered_map>
#include <chrono>

#include "../IntermediatePDDL/PDDLInstance.hh"
#include "../Walker/Walker.hpp"
#include "EntanglementOccurance.hh"

class EntanglementEvaluator {
public:
	struct RunData {
		/// <summary>
		/// The minimum amount of times an action sequence have to occure to be counted as valid
		/// </summary>
		int MinimumOccurance;
	};

	RunData Data;

	unsigned int RemovedCandidates() const { return _RemovedCandidates; }

	EntanglementEvaluator(RunData data) : Data(data) {};

	/// <summary>
	/// Find entanglement candidates from a vector of paths
	/// </summary>
	void EvaluateAndSanitizeCandidates(std::unordered_map<size_t, EntanglementOccurance>* candidates);
private:
	unsigned int _RemovedCandidates;

	/// <summary>
	/// Removes those values in the unordered_map where the occurance is less than the "MinimumOccurance" variable.
	/// </summary>
	void RemoveIfBelowMinimum(std::unordered_map<size_t, EntanglementOccurance>* candidates);
};

#endif