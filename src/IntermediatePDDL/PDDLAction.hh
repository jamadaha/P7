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
    const std::unordered_map<unsigned int, const std::unordered_set<const PDDLLiteral*>> applicableUnaryLiterals;
    // For each parameter, what non unary preconditions mention it
    const std::unordered_map<unsigned int, const std::unordered_set<const PDDLLiteral*>> applicableMultiLiterals;
    PDDLAction() : name("Not Set") {};

    PDDLAction(std::string name, std::vector<std::string> parameters, std::vector<PDDLLiteral> preconditions, std::vector<PDDLLiteral> effects) : 
        name(name), parameters(parameters), preconditions(preconditions), effects(effects), applicableUnaryLiterals(GenerateApplicableLiterals(true)), applicableMultiLiterals(GenerateApplicableLiterals(false)) {};

    PDDLAction(const PDDLAction &a) : 
        name(a.name), parameters(a.parameters), preconditions(a.preconditions), effects(a.effects), applicableUnaryLiterals(GenerateApplicableLiterals(true)), applicableMultiLiterals(GenerateApplicableLiterals(false)) {};

private:
    std::unordered_map<unsigned int, const std::unordered_set<const PDDLLiteral*>> GenerateApplicableLiterals(bool unary) {
        std::unordered_map<unsigned int, const std::unordered_set<const PDDLLiteral*>> set;
        for (int i = 0; i < parameters.size(); i++) {
            std::unordered_set<const PDDLLiteral*> tempSet;
            for (int literalIndex = 0; literalIndex < preconditions.size(); literalIndex++) {
                const PDDLLiteral *literal = &preconditions.at(literalIndex);
                if (unary ? (literal->args.size() != 1) : (literal->args.size() == 1))
                    continue;
                for (int argIndex = 0; argIndex < literal->args.size(); argIndex++)
                    if (i == literal->args.at(argIndex))
                        tempSet.emplace(literal);
            }
            set.emplace(i, tempSet);
        }
        return set;
    };
};

#endif
