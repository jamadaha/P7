#ifndef ACTION_GENERATOR
#define ACTION_GENERATOR

#include <vector>
#include <string>
#include <map>
#include <set>
#include <iterator>
#include <unordered_map>

#include "../IntermediatePDDL/PDDLActionInstance.hh"
#include "../IntermediatePDDL/PDDLInstance.hh"
#include "../Helpers/AlgorithmHelper.hh"

class ActionGenerator {
public:
    unsigned int GetTotalActionsGenerated() { return totalActions; };
    ActionGenerator(std::vector<PDDLAction> *actions, const unsigned int objectCount) : actions(actions) {
        for (int i = 0; i < objectCount; i++)
            objects.emplace(i);
    };

    /// @brief For a given state, generate all possible action instances
    std::vector<PDDLActionInstance> GenerateActions(PDDLState *state);
    /// @brief For a given action, generate all possible action instances
    std::vector<PDDLActionInstance> GenerateActions(PDDLAction *action, PDDLState *state);

    /// @brief For the given \p action append all possible object permutations to candidate objects, only looks at unary literals
    /// @return Returns true if there is some legal permutation, false if not
    bool GetCandidateObjects(std::vector<std::unordered_set<unsigned int>> &candidateObjects, PDDLAction *action, PDDLState *state);
    /// @brief Finds all object permutations which are legal for the given literals
    /// @param literals Some unary literals
    std::unordered_set<unsigned int> GetCandidateObjects(const std::unordered_set<const PDDLLiteral*> *literals, const PDDLState *state);

    /// @brief Removes those in \p set which do not match the given literals
    /// @param literals Some unary literals
    static void RemoveIllegal(std::unordered_set<unsigned int> &set, const std::unordered_set<const PDDLLiteral*> *literals, const PDDLState *state);

    static std::vector<std::vector<unsigned int>> PermuteAll(std::vector<std::unordered_set<unsigned int>> candidateObjects, std::unordered_map<std::pair<unsigned int, unsigned int>, std::unordered_set<std::pair<unsigned int, unsigned int>>> candidatePairs);

    static void Permute(std::vector<std::unordered_set<unsigned int>> &candidateObjects, std::unordered_map<std::pair<unsigned int, unsigned int>, std::unordered_set<std::pair<unsigned int, unsigned int>>> &candidatePairs, std::vector<std::vector<unsigned int>> *permutations, std::vector<unsigned int> *permutation);

    /// @brief Checks whether the objects are valid for each of the \p literals
    /// @param literals Some multi literals
    static bool IsLegal(const std::vector<PDDLLiteral> *literals, const PDDLState *state, const std::vector<unsigned int> *objects);

private:
    unsigned int totalActions = 0;
    std::vector<PDDLAction> *actions;
    std::unordered_set<unsigned int> objects;

    std::unordered_map<size_t, std::vector<PDDLActionInstance>> ActionsCache;
};

#endif
