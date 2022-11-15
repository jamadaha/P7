#ifndef ACTION_GENERATOR
#define ACTION_GENERATOR

#include "BaseActionGenerator.hpp"

#include "../../IntermediatePDDL/PDDLActionInstance.hh"
#include "../../IntermediatePDDL/PDDLInstance.hh"

class ActionGenerator : public BaseActionGenerator {
public:
    ActionGenerator(const PDDLInstance *instance) : BaseActionGenerator(instance) {};

    /// @brief For a given state, generate all possible action instances
    std::vector<PDDLActionInstance> GenerateActions(const PDDLState *state) override;
    /// @brief For a given action, generate all possible action instances
    std::vector<PDDLActionInstance> GenerateActions(const PDDLAction *action, const PDDLState *state) const;

    /// @brief For the given \p action append all possible object permutations to candidate objects, only looks at unary literals
    /// @return Returns true if there is some legal permutation, false if not
    bool GetCandidateObjects(std::vector<std::unordered_set<unsigned int>> &candidateObjects, const PDDLAction *action, const PDDLState *state) const;
    /// @brief Finds all object permutations which are legal for the given literals
    /// @param literals Some unary literals
    std::unordered_set<unsigned int> GetCandidateObjects(const std::unordered_set<const PDDLLiteral*> *literals, const PDDLState *state) const;

    /// @brief Removes those in \p set which do not match the given literals
    /// @param literals Some unary literals
    static void RemoveIllegal(std::unordered_set<unsigned int> &set, const std::unordered_set<const PDDLLiteral*> *literals, const PDDLState *state);

    static std::vector<std::vector<unsigned int>> PermuteAll(std::vector<std::unordered_set<unsigned int>> candidateObjects, std::unordered_map<std::pair<unsigned int, unsigned int>, std::unordered_set<std::pair<unsigned int, unsigned int>>> candidatePairs);

    static void Permute(std::vector<std::unordered_set<unsigned int>> &candidateObjects, std::unordered_map<std::pair<unsigned int, unsigned int>, std::unordered_set<std::pair<unsigned int, unsigned int>>> &candidatePairs, std::vector<std::vector<unsigned int>> *permutations, std::vector<unsigned int> *permutation);

    /// @brief Checks whether the objects are valid for each of the \p literals
    /// @param literals Some multi literals
    static bool IsLegal(const std::vector<PDDLLiteral> *literals, const PDDLState *state, const std::vector<unsigned int> *objects);
};

#endif
