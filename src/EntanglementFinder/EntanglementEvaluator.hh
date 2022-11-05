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
#include "MacroCandidate.hh"

class EntanglementEvaluator {
public:
	struct RunData {
		double MinimumQualityPercent = 0;
		int MaxCandidates = 1;
	};

	RunData Data;

	unsigned int RemovedCandidates() const { return _RemovedCandidates; }
	unsigned int CombinedCandidates() const { return _CombinedCandidates; }

	EntanglementEvaluator(RunData data) : Data(data) {};

	/// <summary>
	/// Find entanglement candidates from a vector of paths
	/// </summary>
	std::vector<MacroCandidate> EvaluateAndSanitizeCandidates(std::unordered_map<size_t, EntanglementOccurance> candidates);

	std::function<double(double length, double maxLength)> LengthModifier;
	std::function<double(double occurance, double maxOccurance)> OccuranceModifier;

private:
	unsigned int _RemovedCandidates;
	unsigned int _CombinedCandidates;

	/// <summary>
	/// Sets the modifiers to some default values, if they have not been set to begin with.
	/// </summary>
	void SetModifiersIfNotSet();
	/// <summary>
	/// Removes those values in the unordered_map where the occurance is less than the "MinimumOccurance" variable.
	/// </summary>
	void RemoveMinimumQuality(std::vector<MacroCandidate>* candidates);
	/// <summary>
	/// Updates the Quality parameter of the occurances based on their lengths
	/// </summary>
	void SetQualityByLength(std::vector<MacroCandidate>* candidates);
	/// <summary>
	/// Updates the Quality parameter of the occurances based on their occurance value
	/// </summary>
	void SetQualityByOccurance(std::vector<MacroCandidate>* candidates);
	std::vector<MacroCandidate> CombineCandidates(std::unordered_map<size_t, EntanglementOccurance>* candidates);
	/// <summary>
	/// Sorts the candidates into a more usefull vector instead.
	/// </summary>
	std::vector<MacroCandidate> SortCandidates(std::vector<MacroCandidate>* candidates);
};

#endif