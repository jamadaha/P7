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
	std::vector<EntanglementOccurance> EvaluateAndSanitizeCandidates(std::unordered_map<size_t, EntanglementOccurance> candidates);

	std::function<const double(double length, double maxLength)> LengthModifier;
	std::function<const double(double occurance, double maxOccurance)> OccuranceModifier;

private:
	unsigned int _RemovedCandidates;

	/// <summary>
	/// Sets the modifiers to some default values, if they have not been set to begin with.
	/// </summary>
	void SetModifiersIfNotSet();
	/// <summary>
	/// Removes those values in the unordered_map where the occurance is less than the "MinimumOccurance" variable.
	/// </summary>
	void RemoveIfBelowMinimum(std::unordered_map<size_t, EntanglementOccurance>* candidates);
	/// <summary>
	/// Updates the Quality parameter of the occurances based on their lengths
	/// </summary>
	void SetQualityByLength(std::unordered_map<size_t, EntanglementOccurance>* candidates);
	/// <summary>
	/// Updates the Quality parameter of the occurances based on their occurance value
	/// </summary>
	void SetQualityByOccurance(std::unordered_map<size_t, EntanglementOccurance>* candidates);
	/// <summary>
	/// Sorts the candidates into a more usefull vector instead.
	/// </summary>
	std::vector<EntanglementOccurance> SortCandidates(std::unordered_map<size_t, EntanglementOccurance>* candidates);
};

#endif