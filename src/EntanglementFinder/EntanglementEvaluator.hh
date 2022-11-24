#ifndef EntanglementEvaluator_HH
#define EntanglementEvaluator_HH

#include <string>
#include <vector>
#include <math.h>
#include <unordered_map>
#include <chrono>

#include "../IntermediatePDDL/PDDLInstance.hh"
#include "EntanglementOccurance.hh"
#include "EntanglementEvaluatorModifiers.hh"

#include "../Walker/Path.hh"

class EntanglementEvaluator {
public:
	struct RunData {
		double MinimumQualityPercent = 0;
		int MaxCandidates = 1;
	};

	RunData Data;

	unsigned int RemovedCandidates() const { return _RemovedCandidates; }

	EntanglementEvaluator(RunData data) : Data(data) {};

	std::vector<EntanglementOccurance> EvaluateAndSanitizeCandidates(std::unordered_map<size_t, EntanglementOccurance> candidates);

	std::function<double(double length, double maxLength)> LengthModifier;
	std::function<double(double occurance, double maxOccurance)> OccuranceModifier;

private:
	unsigned int _RemovedCandidates;

	void SetModifiersIfNotSet();
	std::vector<EntanglementOccurance> ConvertToVector(std::unordered_map<size_t, EntanglementOccurance>* candidates);
	void RemoveMinimumQuality(std::vector<EntanglementOccurance>* candidates);
	void RemoveIfTooMany(std::vector<EntanglementOccurance>* candidates);
	void SetQualityByLength(std::vector<EntanglementOccurance>* candidates);
	void SetQualityByOccurance(std::vector<EntanglementOccurance>* candidates);
	std::vector<EntanglementOccurance> SortCandidates(std::vector<EntanglementOccurance>* candidates);
};

#endif