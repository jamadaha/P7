#ifndef ACTION_GENERATOR
#define ACTION_GENERATOR

#include <vector>
#include <string>
#include <map>
#include <set>
#include <iterator>

#include "../IntermediatePDDL/PDDLActionInstance.hh"
#include "../IntermediatePDDL/PDDLInstance.hh"

class ActionGenerator {
public:
    ActionGenerator(const PDDLDomain *domain, const PDDLProblem *problem) : domain(domain), problem(problem) {
    };
    /// @brief For a given state, generate all possible action instances
    std::vector<PDDLActionInstance> GenerateActions(const PDDLState *state);
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
    /// @brief Removes those in \p set which do not match the given literal
    /// @param literal Some unary literal
    static void RemoveIllegal(std::unordered_set<unsigned int> &set, const PDDLLiteral *literal, const PDDLState *state);

    /// @brief Removes those in \p set which do not match the given literal
    /// @param literal Some unary literal
    static void RemoveIllegal(std::unordered_set<std::pair<unsigned int, unsigned int>> &set, const PDDLLiteral *literal, const PDDLState *state);

    static void Intersect(std::unordered_set<unsigned int> &a, const std::unordered_set<unsigned int> &b);

    unsigned int GetTotalActionsGenerated() { return totalActions; };

private:
    const PDDLDomain *domain;
    const PDDLProblem *problem;
    unsigned int totalActions = 0;
};

#endif
