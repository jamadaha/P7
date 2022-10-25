#ifndef EntanglementOccurance_HH
#define EntanglementOccurance_HH

#include <vector>

#include "../IntermediatePDDL/PDDLInstance.hh"

struct EntanglementOccurance {
public:
    size_t GetHash();
	const std::vector<PDDLActionInstance> Chain;
    mutable int Occurance;

    struct EntangleCmp {
		bool operator()(const EntanglementOccurance& lhs, const EntanglementOccurance& rhs) const { 
			return lhs.Hash == rhs.Hash; 
		};
	};
    EntanglementOccurance(const std::vector<PDDLActionInstance> chain) : Chain(chain), Occurance(2) {};
    EntanglementOccurance(const std::vector<PDDLActionInstance> chain, size_t hash) : Chain(chain), Occurance(2), Hash(hash) {};
private:
    size_t Hash = 0;
};

namespace std {
    template <>
    struct hash<EntanglementOccurance> {
        auto operator()(const EntanglementOccurance& occ) const -> size_t {
            return hash<const vector<PDDLActionInstance>>{}(occ.Chain);
        }
    };
}

#endif