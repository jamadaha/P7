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

    std::vector<PDDLLiteral> unaryPreconditions;
    std::vector<PDDLLiteral> binaryPreconditions;

    // For each parameter, what unary preconditions mention it
    const std::vector<std::unordered_set<const PDDLLiteral*>> applicableUnaryLiterals;
    // For each parameter, what unary predicates are mentioned in applicable preconditions
    const std::vector<std::unordered_set<unsigned int>> applicableUnaryPredicates;
    // For each parameter, what non unary preconditions mention it
    const std::vector<std::unordered_set<const PDDLLiteral*>> applicableMultiLiterals;
    PDDLAction() : name("Not Set") {};
    PDDLAction(std::string name) : name(name) {};

    PDDLAction(std::string name, std::vector<std::string> parameters, std::vector<PDDLLiteral> preconditions, std::vector<PDDLLiteral> effects) : 
        name(name), parameters(parameters), preconditions(preconditions), effects(effects), applicableUnaryLiterals(GenerateApplicableLiterals(true)), applicableMultiLiterals(GenerateApplicableLiterals(false)) {
        for (auto predicate = preconditions.begin(); predicate != preconditions.end(); predicate++) {
            if (predicate->args.size() == 1)
                unaryPreconditions.push_back(*predicate);
            else if (predicate->args.size() == 2)
                binaryPreconditions.push_back(*predicate);
        }
    };

    PDDLAction(const PDDLAction &a) : 
        name(a.name), parameters(a.parameters), preconditions(a.preconditions), effects(a.effects), 
        applicableUnaryLiterals(GenerateApplicableLiterals(true)), 
        applicableMultiLiterals(GenerateApplicableLiterals(false)),
        applicableUnaryPredicates(GenerateApplicablePredicates(true)) {
        for (auto predicate = a.preconditions.begin(); predicate != a.preconditions.end(); predicate++) {
            if (predicate->args.size() == 1)
                unaryPreconditions.push_back(*predicate);
            else if (predicate->args.size() == 2)
                binaryPreconditions.push_back(*predicate);
        }
    };

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
    std::vector<std::unordered_set<unsigned int>> GenerateApplicablePredicates(bool unary) const;
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
