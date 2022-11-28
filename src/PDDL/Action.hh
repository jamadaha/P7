#ifndef PDDL_ACTION_HH
#define PDDL_ACTION_HH

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stdexcept>

#include "Literal.hh"

namespace PDDL {
    class Action {
    public:
        const std::string name;
        const std::vector<std::string> parameters;
        const std::vector<Literal> preconditions;
        const std::vector<Literal> effects;

        std::vector<Literal> unaryPreconditions;
        std::vector<Literal> binaryPreconditions;

        // For each parameter, what unary preconditions mention it
        const std::vector<std::unordered_set<const Literal*>> applicableUnaryLiterals;
        // For each parameter, what unary predicates are mentioned in applicable preconditions
        const std::vector<std::unordered_set<unsigned int>> applicableUnaryPredicates;
        const std::vector<std::unordered_set<unsigned int>> applicablePredicates;
        // For each parameter, what non unary preconditions mention it
        const std::vector<std::unordered_set<const Literal*>> applicableMultiLiterals;

        Action() : name("Not Set") {};
        Action(std::string name) : name(name) {};

        Action(std::string name, std::vector<std::string> parameters, std::vector<Literal> preconditions, std::vector<Literal> effects) :
            name(name),
            parameters(parameters),
            preconditions(preconditions),
            effects(effects),
            applicableUnaryLiterals(GenerateApplicableLiterals(true)),
            applicableUnaryPredicates(GenerateApplicablePredicates(true)),
            applicablePredicates(GenerateApplicablePredicates()),
            applicableMultiLiterals(GenerateApplicableLiterals(false)) {
            for (auto predicate = preconditions.begin(); predicate != preconditions.end(); predicate++) {
                if (predicate->args.size() == 1)
                    unaryPreconditions.push_back(*predicate);
                else if (predicate->args.size() == 2)
                    binaryPreconditions.push_back(*predicate);
            }
        };

        Action(const PDDL::Action& a) :
            name(a.name),
            parameters(a.parameters),
            preconditions(a.preconditions),
            effects(a.effects),
            applicableUnaryLiterals(GenerateApplicableLiterals(true)),
            applicableUnaryPredicates(GenerateApplicablePredicates(true)),
            applicablePredicates(GenerateApplicablePredicates()),
            applicableMultiLiterals(GenerateApplicableLiterals(false)) {
            for (auto predicate = preconditions.begin(); predicate != preconditions.end(); predicate++) {
                if (predicate->args.size() == 1)
                    unaryPreconditions.push_back(*predicate);
                else if (predicate->args.size() == 2)
                    binaryPreconditions.push_back(*predicate);
            }
        }

        /// @return Returns true if name, parameters and preconditions are the same, ignores parameter names
        friend bool operator==(const Action& lhs, const Action& rhs) {
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
        std::vector<std::unordered_set<const Literal*>> GenerateApplicableLiterals(bool unary) const;
        std::vector<std::unordered_set<unsigned int>> GenerateApplicablePredicates() const;
        std::vector<std::unordered_set<unsigned int>> GenerateApplicablePredicates(bool unary) const;
    };
}

namespace std {
    template <>
    struct hash<const PDDL::Action*> {
        auto operator()(const PDDL::Action* s) const -> size_t {
            return hash<string>{}(s->name) << s->preconditions.size() << s->effects.size() << s->parameters.size();
        }
    };
}

#endif
