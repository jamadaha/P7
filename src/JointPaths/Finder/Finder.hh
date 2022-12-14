#ifndef JOINTPATHFINDER_HH
#define JOINTPATHFINDER_HH

#include <vector>
#include <unordered_map>
#include <chrono>
#include <math.h>

#include "../PDDL/Instance.hh"
#include "../JointPath.hh"
#include "../Walker/Path.hh"

namespace JointPaths {

	class Finder {
	public:
		struct RunData {
			enum LevelReductionTypes { None, Division, Subtraction };

			/// <summary>
			/// The ceiling of the search (leave as -1 if you want the full path size)
			/// </summary>
			int SearchCeiling = -1;
			/// <summary>
			/// The floor of the search, minimum is 2 and maximum is the full length of the path
			/// </summary>
			int SearchFloor = 2;
			/// <summary>
			/// By how much the level should be reduced in each iteration.
			/// </summary>
			double LevelReductionFactor = 2;
			int TimeLimitMs = 100;
			LevelReductionTypes LevelReductionType = LevelReductionTypes::Division;
		};

		RunData Data;

		int CurrentLevel() const { return _CurrentLevel; }
		int TotalLevels() const { return _TotalLevels; }
		unsigned int TotalComparisons() const { return _TotalComparisons; }

		Finder(RunData data) : Data(data) {};

		/// <summary>
		/// Find entanglement candidates from a vector of paths
		/// </summary>
		std::unordered_map<size_t, JointPath> FindEntangledCandidates(std::vector<Path>* paths);

		std::function<const void(int level, int outOf)> OnNewLevel;
		std::function<const void()> OnLevelEnd;
		std::function<const void(int current, int outOf)> OnLevelIteration;
		std::function<const void()> OnTimeLimitReached;

	private:
		int _CurrentLevel;
		int _TotalLevels;
		unsigned int _TotalComparisons;
		bool _HasTimeLimit = false;
		bool _IsTimeLimitReached = false;
		std::chrono::_V2::steady_clock::time_point _StartTime;

		/// <summary>
		/// Validate the input data
		/// </summary>
		int GetInitialLevelIfValid(std::vector<Path>* paths);
		/// <summary>
		/// Takes a set of Paths and splits them up into sets of PDDLActionInstances based on the level.
		/// </summary>
		void GenerateActionSet(std::vector<std::pair<size_t, std::vector<PDDL::ActionInstance*>>>* currentValues, std::vector<Path>* paths, const int level);
		/// <summary>
		/// Based on the values generated in the "GenerateActionSet" method
		/// </summary>
		void AddCandidatesIfThere(std::unordered_map<size_t, JointPath>* candidates, const std::vector<std::pair<size_t, std::vector<PDDL::ActionInstance*>>>* currentValues);
		/// <summary>
		/// Returns true if the time limit have been exceeded
		/// </summary>
		bool IsOverTimeLimit();
		/// <summary>
		/// Reduce the current level
		/// </summary>
		int ReduceLevel(int level);
	};
}

#endif