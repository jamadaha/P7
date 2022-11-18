#ifndef EntanglementOccurance_HH
#define EntanglementOccurance_HH

#include <vector>

#include "../IntermediatePDDL/PDDLInstance.hh"

struct EntanglementOccurance {
public:
    size_t GetHash();
	std::vector<PDDLActionInstance> Chain;
    int Occurance;
    double Quality = 1;

    EntanglementOccurance(std::vector<PDDLActionInstance*> chain, size_t hash) : Occurance(2), Hash(hash) {
        for (auto instance : chain)
            Chain.push_back(*instance);
    };
private:
    size_t Hash = 0;
};

#endif