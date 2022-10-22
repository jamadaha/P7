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
    ActionGenerator(PDDLDomain *domain, PDDLProblem *problem) : domain(domain), problem(problem) {};
    /// @brief For a given state, generate all possible action instances
    std::vector<PDDLActionInstance> GenerateActions(const PDDLState *state) const;
    /// @brief For a given action, generate all possible action instances
    std::vector<PDDLActionInstance> GenerateActions(const PDDLAction *action, const PDDLState *state) const;
    /// @brief Removes those in \p set which do not match the given literals
    /// @param literals Some unary literals
    static void RemoveIllegal(std::unordered_set<unsigned int> &set, const std::unordered_set<const PDDLLiteral*> *literals, const PDDLState *state);
    /// @brief Removes those in \p set which do not match the given literal
    /// @param literal Some unary literal
    static void RemoveIllegal(std::unordered_set<unsigned int> &set, const PDDLLiteral *literal, const PDDLState *state);
    /// @brief Finds next permutation of the \p iteration
    /// @return Returns true if it hasn't reached the final permutation, and false if it has
    static bool Iterate(std::vector<std::unordered_set<unsigned int>::iterator> *iteration, std::vector<std::unordered_set<unsigned int>> *candidateObjects);
private:
    PDDLDomain *domain;
    PDDLProblem *problem;
     // Given some action generate all legal parameter variations
    
    std::unordered_set<unsigned int> GetCandidateObjects(const std::unordered_set<const PDDLLiteral*> *literals, const PDDLState *state) const;
    bool IsLegal(const std::vector<PDDLLiteral> *literals, const PDDLState *state, std::vector<unsigned int> *objects) const;
    
};

#endif
