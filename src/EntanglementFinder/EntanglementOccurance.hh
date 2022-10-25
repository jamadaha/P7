#ifndef EntanglementOccurance_HH
#define EntanglementOccurance_HH

#include <vector>

#include "../IntermediatePDDL/PDDLInstance.hh"

struct EntanglementOccurance {
public:
	const std::vector<PDDLActionInstance> Chain;
    mutable int Occurance;
	EntanglementOccurance(const std::vector<PDDLActionInstance> chain) : Chain(chain), Occurance(2){};
    friend bool operator==(const EntanglementOccurance &lhs, const EntanglementOccurance& rhs) {
        return lhs.Chain == rhs.Chain;
    }
    struct EntangleCmp {
		bool operator()(const EntanglementOccurance& lhs, const EntanglementOccurance& rhs) const { 
			return lhs == rhs; 
		};
	};
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