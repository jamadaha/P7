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

    /// @brief Given a a set of candidateObjects for each parameter of an action, this function generates for each pair of parameters all legal pairings of objects.
    /// @param candidateObjects Removes those that are in no legal pairings
    /// @return All legal pairs for all index pairs. Note if some index pair doesn't have a precondition, then that pair isn't in the map.
    static std::unordered_map<std::pair<unsigned int, unsigned int>, std::unordered_set<std::pair<unsigned int, unsigned int>>>
        GetLegalPairings(   const PDDLAction* action, const PDDLState *state,
                            std::vector<std::unordered_set<unsigned int>> *candidateObjects);
                            
private:
    static LegalPairInformation GenerateLegalPairings(  const PDDLLiteral* literal,
                                                        const PDDLState *state,
                                                        const std::vector<std::unordered_set<unsigned int>> *candidateObjects,
                                                        const std::pair<unsigned int, unsigned int> *indexPair);

    /// @brief For the given indexPair, it removes those candidateObjects that appear in no pairings.
    static void UpdateCandidateObjects( const std::pair<unsigned int, unsigned int> *indexPair, 
                                        std::vector<std::unordered_set<unsigned int>> *candidateObjects,
                                        const LegalPairInformation *newInformation);

    static void UpdateLegalPairings(
        const std::pair<unsigned int, unsigned int> *indexPair,
        std::unordered_map<std::pair<unsigned int, unsigned int>, std::unordered_set<std::pair<unsigned int, unsigned int>>> *candidatePairs,
        const LegalPairInformation *newInformation);
};

#endif