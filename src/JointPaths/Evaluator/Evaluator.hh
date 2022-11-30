#ifndef JOINTPATH_EVALUATOR_HH
#define JOINTPATH_EVALUATOR_HH

#include <vector>
#include <unordered_map>

#include "../JointPath.hh"
#include "EvaluationModifiers.hh"

namespace JointPaths {
	class Evaluator {
	public:
		struct RunData {
			double MinimumQualityPercent = 0;
			int MaxCandidates = 1;
		};

		RunData Data;

		inline unsigned int RemovedCandidates() const { return _RemovedCandidates; }

		Evaluator(RunData data) : Data(data) {};

		std::vector<JointPath> EvaluateAndSanitizeCandidates(std::unordered_map<size_t, JointPath> candidates);

		std::function<double(double length, double maxLength)> LengthModifier;
		std::function<double(double occurance, double maxOccurance)> OccuranceModifier;

	private:
		unsigned int _RemovedCandidates;
		const std::function<bool((const JointPath& candidate))> RemoveIfLessThanFunc = [&](const JointPath& candidate) { return candidate.Quality < Data.MinimumQualityPercent; };

		void SetModifiersIfNotSet();
		std::vector<JointPath> ConvertToVector(std::unordered_map<size_t, JointPath>* candidates);
		void RemoveMinimumQuality(std::vector<JointPath>* candidates);
		void RemoveIfTooMany(std::vector<JointPath>* candidates);
		void SetQualityByLength(std::vector<JointPath>* candidates);
		void SetQualityByOccurance(std::vector<JointPath>* candidates);
		std::vector<JointPath> SortCandidates(std::vector<JointPath>* candidates);
	};

}

#endif