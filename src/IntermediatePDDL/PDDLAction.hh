#ifndef PDDL_ACTION_HH
#define PDDL_ACTION_HH

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stdexcept>

#include "PDDLLiteral.hh"

struct PDDLAction {
    const std::string name;
    const std::vector<std::string> parameters;
    const std::vector<PDDLLiteral> preconditions;
    const std::vector<PDDLLiteral> effects;
    // For each parameter, what unary preconditions mention it
    const std::vector<std::unordered_set<const PDDLLiteral*>> applicableUnaryLiterals;
    // For each parameter, what unary predicates are mentioned in applicable preconditions
    const std::vector<std::unordered_set<unsigned int>> applicablePredicates;
    // For each parameter, what non unary preconditions mention it
    const std::vector<std::unordered_set<const PDDLLiteral*>> applicableMultiLiterals;
    // Defines preconditions clusters
    // A cluster is a set of parameters that are interlinked, either through preconditions or effects
    // Specifically for this variable it is through precondition
    const std::unordered_set<std::unordered_set<unsigned int>> preClusters;
    // Links each parameter to their respective cluster, if it exists, if not it is a nullptr
    const std::vector<std::unordered_set<unsigned int>*> preClusterMembership;
    // Defines effect clusters
    const std::unordered_set<std::unordered_set<unsigned int>> effClusters;
    // Links each parameter to their respective cluster, if it exists, if not it is a nullptr
    const std::vector<std::unordered_set<unsigned int>*> effClusterMembership;
    PDDLAction() : name("Not Set") {};
    PDDLAction(std::string name) : name(name) {};

    PDDLAction(std::string name, std::vector<std::string> parameters, std::vector<PDDLLiteral> preconditions, std::vector<PDDLLiteral> effects) : 
        name(name), parameters(parameters), preconditions(preconditions), effects(effects), 
        applicableUnaryLiterals(GenerateApplicableLiterals(true)), 
        applicableMultiLiterals(GenerateApplicableLiterals(false)),
        applicablePredicates(GenerateApplicablePredicates()),
        preClusters(GenerateClusters(&preconditions)),
        effClusters(GenerateClusters(&effects)) {};

    PDDLAction(const PDDLAction &a) : 
        name(a.name), parameters(a.parameters), preconditions(a.preconditions), effects(a.effects), 
        applicableUnaryLiterals(GenerateApplicableLiterals(true)), 
        applicableMultiLiterals(GenerateApplicableLiterals(false)),
        applicablePredicates(GenerateApplicablePredicates()),
        preClusters(GenerateClusters(&preconditions)),
        effClusters(GenerateClusters(&effects)) {};

    /// @return Returns true if name, parameters and preconditions are the same, ignores parameter names
    friend bool operator==(const PDDLAction& lhs, const PDDLAction& rhs) {
        if (lhs.name.compare(rhs.name) != 0)
            return false;
        if (lhs.parameters.size() != rhs.parameters.size())
            return false;
        if (lhs.preconditions != rhs.preconditions)
            return false;
        if (lhs.effects != rhs.effects)
            return false;
        return true;
    }

private:
    std::vector<std::unordered_set<const PDDLLiteral*>> GenerateApplicableLiterals(bool unary) const;
    std::vector<std::unordered_set<unsigned int>> GenerateApplicablePredicates() const;
    std::unordered_set<std::unordered_set<unsigned int>> GenerateClusters(const std::vector<PDDLLiteral> *literals) const;
};

namespace std {
    template <>
    struct hash<const PDDLAction*> {
        auto operator()(const PDDLAction* s) const -> size_t {
            return hash<string>{}(s->name) << s->preconditions.size() << s->effects.size() << s->parameters.size();
        }
    };
}

#endif
