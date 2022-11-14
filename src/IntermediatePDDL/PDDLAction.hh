#ifndef PDDL_ACTION_HH
#define PDDL_ACTION_HH

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stdexcept>

#include "PDDLLiteral.hh"

struct PDDLAction {
public:
    const std::string name;
    const std::vector<std::string> parameters;
    const std::vector<PDDLLiteral> preconditions;
    const std::vector<PDDLLiteral> effects;
    // For each parameter, what unary preconditions mention it
    const std::vector<std::unordered_set<const PDDLLiteral*>> applicableUnaryLiterals;
    // For each parameter, what unary predicates are mentioned in applicable preconditions
    const std::vector<std::unordered_set<unsigned int>> applicableUnaryPredicates;
    const std::vector<std::unordered_set<unsigned int>> applicablePredicates;
    // For each parameter, what non unary preconditions mention it
    const std::vector<std::unordered_set<const PDDLLiteral*>> applicableMultiLiterals;
    const std::vector<bool> staticParameters;

    PDDLAction() : name("Not Set") {};
    PDDLAction(std::string name) : name(name) {};

    PDDLAction(std::string name, std::vector<std::string> parameters, std::vector<PDDLLiteral> preconditions, std::vector<PDDLLiteral> effects) : 
        name(name), parameters(parameters), preconditions(preconditions), effects(effects), applicableUnaryLiterals(GenerateApplicableLiterals(true)), applicableMultiLiterals(GenerateApplicableLiterals(false)),
        applicablePredicates(GenerateApplicablePredicates()) {};

    PDDLAction(const PDDLAction &a) : 
    name(a.name),
    parameters(a.parameters),
    preconditions(a.preconditions),
    effects(a.effects),
    applicableUnaryLiterals(a.applicableUnaryLiterals),
    applicableUnaryPredicates(a.applicableUnaryPredicates),
    applicablePredicates(a.applicablePredicates),
    applicableMultiLiterals(a.applicableMultiLiterals),
    staticParameters(a.staticParameters) {}
    
    PDDLAction(const PDDLAction &a, const std::unordered_set<unsigned int> *staticPredicates) :
    name(a.name),
    parameters(a.parameters),
    preconditions(a.preconditions),
    effects(a.effects),
    applicableUnaryLiterals(a.applicableUnaryLiterals),
    applicableUnaryPredicates(a.applicableUnaryPredicates),
    applicablePredicates(a.applicablePredicates),
    applicableMultiLiterals(a.applicableMultiLiterals),
    staticParameters(GenerateStaticParameters(staticPredicates)) {}

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
    std::vector<std::unordered_set<unsigned int>> GenerateApplicablePredicates(bool unary) const;
    std::vector<bool> GenerateStaticParameters(const std::unordered_set<unsigned int> *staticPredicates) const;
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
