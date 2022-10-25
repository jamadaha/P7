#ifndef EntanglementOccurance_HH
#define EntanglementOccurance_HH

#include <vector>

#include "../IntermediatePDDL/PDDLInstance.hh"

struct EntanglementOccurance {
public:
	const std::vector<PDDLActionInstance> Chain;
    mutable int Occurance;
	EntanglementOccurance(const std::vector<PDDLActionInstance> chain) : Chain(chain), Occurance(2){};
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