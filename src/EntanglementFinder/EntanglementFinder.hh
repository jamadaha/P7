#ifndef EntanglementFinder_HH
#define EntanglementFinder_HH

#include <string>
#include <vector>
#include <math.h>
#include <unordered_set>

#include "../IntermediatePDDL/PDDLInstance.hh"
#include "../Walker/Walker.hpp"

class EntanglementFinder {
public:
	const int SearchCeiling;
	const int SearchFloor;

	EntanglementFinder(int searchFloor = 2, int searchCeiling = -1) : SearchCeiling(searchCeiling), SearchFloor(searchFloor){};

	std::unordered_set<std::vector<PDDLActionInstance>> FindEntangledCandidates(std::vector<Path> paths);
};

#endif