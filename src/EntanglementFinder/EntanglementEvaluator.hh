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
#include "EntanglementEvaluatorModifiers.hh"

class EntanglementEvaluator {
public:
	struct RunData {
		/// <summary>
		/// What bottom percentage of candidates to cut away from the candidates
		/// </summary>
		double MinimumOccurancePercent = 5;
		/// <summary>
		/// What bottom percentage of candidates to cut away from the candidates
		/// </summary>
		double MinimumCrossOccurancePercent = 5;
	};

	RunData Data;

	unsigned int RemovedCandidates() const { return _RemovedCandidates; }

	EntanglementEvaluator(RunData data) : Data(data) {};

	/// <summary>
	/// Find entanglement candidates from a vector of paths
	/// </summary>
	std::vector<EntanglementOccurance> EvaluateAndSanitizeCandidates(std::unordered_map<size_t, EntanglementOccurance> candidates);

	std::function<double(double length, double maxLength)> LengthModifier;
	std::function<double(double occurance, double maxOccurance)> OccuranceModifier;

private:
	unsigned int _RemovedCandidates;
	int _MinimumOccurance = 1;
	int _MinimumCrossOccurance = 1;

	/// <summary>
	/// Sets the modifiers to some default values, if they have not been set to begin with.
	/// </summary>
	void SetModifiersIfNotSet();
	/// <summary>
	/// Sets the modifiers to some default values, if they have not been set to begin with.
	/// </summary>
	void FindMinimumOccurances(std::unordered_map<size_t, EntanglementOccurance>* candidates);
	/// <summary>
	/// Removes those values in the unordered_map where the occurance is less than the "MinimumOccurance" variable.
	/// </summary>
	void RemoveMinimumOccurances(std::unordered_map<size_t, EntanglementOccurance>* candidates);
	/// <summary>
	/// Removes those values in the unordered_map where the occurance is less than the "MinimumCrossOccurance" variable.
	/// </summary>
	void RemoveMinimumCrossOccurances(std::unordered_map<size_t, EntanglementOccurance>* candidates);
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