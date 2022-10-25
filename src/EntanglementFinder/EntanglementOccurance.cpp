#include "EntanglementOccurance.hh"

using namespace std;

size_t EntanglementOccurance::GetHash() {
    if (Hash != 0)
        return Hash;
    Hash = hash<const vector<PDDLActionInstance>>{}((*this).Chain);
    return Hash;
}