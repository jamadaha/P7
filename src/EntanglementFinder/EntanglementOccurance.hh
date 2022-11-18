#ifndef EntanglementOccurance_HH
#define EntanglementOccurance_HH

#include <vector>

#include "../IntermediatePDDL/PDDLInstance.hh"

struct EntanglementOccurance {
public:
    size_t GetHash();
	std::vector<PDDLActionInstance*> Chain;
    int Occurance;
    double Quality = 1;

    EntanglementOccurance(std::vector<PDDLActionInstance*> chain) : Chain(chain), Occurance(2) {};
    EntanglementOccurance(std::vector<PDDLActionInstance*> chain, size_t hash) : Chain(chain), Occurance(2), Hash(hash) {};
private:
    size_t Hash = 0;
};

#endif