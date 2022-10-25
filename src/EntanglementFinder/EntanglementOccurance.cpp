#include "EntanglementOccurance.hh"

size_t EntanglementOccurance::GetHash() {
    if (Hash != 0)
        return Hash;
    Hash = std::hash<EntanglementOccurance>{}(*this);
    return Hash;
}