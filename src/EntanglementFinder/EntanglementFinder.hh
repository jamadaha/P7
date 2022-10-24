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
	std::unordered_set<std::vector<PDDLActionInstance>> FindEntangledCandidates(PDDLInstance* instance, std::vector<Path> paths);
};

#endif