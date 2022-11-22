#ifndef ACTION_GENERATOR
#define ACTION_GENERATOR

#include <vector>
#include <string>
#include <map>
#include <set>
#include <iterator>

#include "UnaryFactVerifier.hpp"
#include "BinaryFactVerifier.hpp"

class ActionGenerator {
public:
    unsigned int GetTotalActionsGenerated() { return totalActions; };
    ActionGenerator(const std::vector<PDDLAction> *actions, const unsigned int objectCount) : 
    actions(actions), unaryFactVerifier(UnaryFactVerifier(objectCount)) {};

    /// @brief For a given state, generate all possible action instances
    std::vector<PDDLActionInstance> GenerateActions(const PDDLState *state);
    /// @brief For a given action, generate all possible action instances
    std::vector<PDDLActionInstance> GenerateActions(const PDDLAction *action, const PDDLState *state) const;

    static std::vector<std::vector<unsigned int>> PermuteAll(std::vector<std::unordered_set<unsigned int>> candidateObjects, std::unordered_map<std::pair<unsigned int, unsigned int>, std::unordered_set<std::pair<unsigned int, unsigned int>>> candidatePairs);

    static void Permute(std::vector<std::unordered_set<unsigned int>> &candidateObjects, std::unordered_map<std::pair<unsigned int, unsigned int>, std::unordered_set<std::pair<unsigned int, unsigned int>>> &candidatePairs, std::vector<std::vector<unsigned int>> *permutations, std::vector<unsigned int> *permutation);

private:
    unsigned int totalActions = 0;
    const std::vector<PDDLAction> *actions;
    UnaryFactVerifier unaryFactVerifier;
    BinaryFactVerifier binaryFactVerifier;
};

#endif
