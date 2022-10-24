#ifndef EntanglementFinder_HH
#define EntanglementFinder_HH

#include <string>
#include <vector>
#include <math.h>

#include "../IntermediatePDDL/PDDLInstance.hh"
#include "../Walker/Walker.hpp"
#include "EntangledActionsSet.hh"

class EntanglementFinder {
public:
	std::vector<EntangledActionsSet> FindEntangledCandidates(PDDLInstance* instance, std::vector<Path> paths);
};

#endif