#ifndef BINARY_FACT_VERIFIER
#define BINARY_FACT_VERIFIER

#include <unordered_map>
#include <unordered_set>

#include "../../IntermediatePDDL/PDDLAction.hh"
#include "../../IntermediatePDDL/PDDLState.hh"

#include "../../Helpers/AlgorithmHelper.hh"

class BinaryFactVerifier {
public:
    BinaryFactVerifier() {};

    static std::unordered_map<std::pair<unsigned int, unsigned int>, std::unordered_set<std::pair<unsigned int, unsigned int>>>
        GetLegalPairings(   const PDDLAction* action, const PDDLState *state,
                            std::vector<std::unordered_set<unsigned int>> *candidateObjects);
private:

};

#endif