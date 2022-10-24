#ifndef EntangledActionsSet_HH
#define EntangledActionsSet_HH

#include <vector>

#include "../IntermediatePDDL/PDDLInstance.hh"

struct EntangledActionsSet {
	int Hash;
	std::vector<PDDLActionInstance> Set;
	EntangledActionsSet(int hash, std::vector<PDDLActionInstance> set) : Hash(hash), Set(set)
	{};
};

#endif