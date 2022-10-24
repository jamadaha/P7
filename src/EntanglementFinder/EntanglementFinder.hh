#ifndef EntanglementFinder_HH
#define EntanglementFinder_HH

#include <string>
#include <vector>
#include <math.h>
#include <unordered_set>

#include "../IntermediatePDDL/PDDLInstance.hh"
#include "../Walker/Walker.hpp"
#include "EntanglementOccurance.hh"

class EntanglementFinder {
public:
	/// <summary>
	/// The ceiling of the search (leave as -1 if you want the full path size)
	/// </summary>
	const int SearchCeiling;

	/// <summary>
	/// The floor of the search, minimum is 2 and maximum is the full length of the path
	/// </summary>
	const int SearchFloor;

	/// <summary>
	/// By how much the level should be reduced in each iteration.
	/// </summary>
	const double LevelReductionFactor;

	EntanglementFinder(int searchFloor = 2, int searchCeiling = -1, double levelReductionFactor = 2) : SearchCeiling(searchCeiling), SearchFloor(searchFloor), LevelReductionFactor(levelReductionFactor) {};

	/// <summary>
	/// Find entanglement candidates from a vector of paths
	/// </summary>
	std::unordered_set<EntanglementOccurance> FindEntangledCandidates(std::vector<Path> paths);

private:
	std::vector<std::vector<PDDLActionInstance>> GenerateActionSet(std::vector<Path> paths, int level);
	void AddCandidatesIfThere(std::unordered_set<EntanglementOccurance>* candidates, std::vector<std::vector<PDDLActionInstance>> currentValues);
};

#endif