#ifndef BASE_ACTION_GENERATOR
#define BASE_ACTION_GENERATOR

#include <vector>
#include <string>
#include <map>
#include <set>
#include <iterator>

#include "../../IntermediatePDDL/PDDLActionInstance.hh"
#include "../../IntermediatePDDL/PDDLInstance.hh"

class BaseActionGenerator {
public:
    unsigned int GetTotalActionsGenerated() { return totalActions; };
    BaseActionGenerator(const PDDLInstance *instance) : instance(instance) {
        srand(time(NULL));
    };

    // Generates a single action for the given state
    virtual PDDLActionInstance GenerateRandomAction(const PDDLState *state) = 0;

    // Generates all possible actions for the given state
    virtual std::vector<PDDLActionInstance> GenerateActions(const PDDLState *state) = 0;

    static std::vector<std::vector<unsigned int>> PermuteAll(std::vector<std::unordered_set<unsigned int>> *candidateObjects, std::unordered_map<std::pair<unsigned int, unsigned int>, std::unordered_set<std::pair<unsigned int, unsigned int>>> *candidatePairs);
    static void Permute(std::vector<std::unordered_set<unsigned int>> *candidateObjects, std::unordered_map<std::pair<unsigned int, unsigned int>, std::unordered_set<std::pair<unsigned int, unsigned int>>> *candidatePairs, std::vector<std::vector<unsigned int>> *permutations, std::vector<unsigned int> *permutation);

protected:
    const PDDLInstance *instance;
    unsigned int totalActions = 0;
};

#endif
