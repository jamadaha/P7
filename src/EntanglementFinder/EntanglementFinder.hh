#ifndef EntanglementFinder_HH
#define EntanglementFinder_HH

#include <string>
#include <fstream>
#include <streambuf>
#include <vector>

#include "../IntermediatePDDL/PDDLInstance.hh"
#include "../Walker/Walker.hpp"

class EntanglementFinder {
public:
	std::vector<std::vector<PDDLActionInstance>> FindEntangledCandidates(std::vector<Path> paths);
};

#endif