#ifndef BINARY_FACT_VERIFIER
#define BINARY_FACT_VERIFIER

#include <unordered_map>
#include <unordered_set>

#include "../../IntermediatePDDL/PDDLAction.hh"
#include "../../IntermediatePDDL/PDDLState.hh"

#include "../../Helpers/AlgorithmHelper.hh"

struct LegalPairInformation{
    // Set of legal pairings
    std::unordered_set<std::pair<unsigned int, unsigned int>> pairs;
    // Set of objects appearing in the left side of a legal pair
    std::unordered_set<unsigned int> indexFirst;
    // Set of objects appearing in the right side of a legal pair
    std::unordered_set<unsigned int> indexSecond;
};

class BinaryFactVerifier {
public:
    BinaryFactVerifier() {};

    static std::unordered_map<std::pair<unsigned int, unsigned int>, std::unordered_set<std::pair<unsigned int, unsigned int>>>
        GetLegalPairings(   const PDDLAction* action, const PDDLState *state,
                            std::vector<std::unordered_set<unsigned int>> *candidateObjects);
private:
    static LegalPairInformation GenerateLegalPairings(  const PDDLLiteral* literal,
                                                        const PDDLState *state,
                                                        const std::vector<std::unordered_set<unsigned int>> *candidateObjects,
                                                        const std::pair<unsigned int, unsigned int> indexPair);
    static void UpdateCandidateObjects( const std::pair<unsigned int, unsigned int> indexPair, 
                                        std::vector<std::unordered_set<unsigned int>> *candidateObjects,
                                        const LegalPairInformation *newInformation);
    static void UpdateLegalPairings(
        const std::pair<unsigned int, unsigned int> indexPair,
        std::unordered_map<std::pair<unsigned int, unsigned int>, std::unordered_set<std::pair<unsigned int, unsigned int>>> *candidatePairs,
        const LegalPairInformation *newInformation);
};

#endif