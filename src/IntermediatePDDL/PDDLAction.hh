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
    // For each parameter, what preconditions mention it
    const std::unordered_map<unsigned int, const std::unordered_set<const PDDLLiteral*>> applicableLiterals;
    PDDLAction() : name("Not Set") {};

    PDDLAction(std::string name, std::vector<std::string> parameters, std::vector<PDDLLiteral> preconditions, std::vector<PDDLLiteral> effects) : 
        name(name), parameters(parameters), preconditions(preconditions), effects(effects), applicableLiterals(GenerateApplicableLiterals()) {};

    PDDLAction(const PDDLAction &a) : 
        name(a.name), parameters(a.parameters), preconditions(a.preconditions), effects(a.effects), applicableLiterals(GenerateApplicableLiterals()) {};

private:
    std::unordered_map<unsigned int, const std::unordered_set<const PDDLLiteral*>> GenerateApplicableLiterals() {
        std::unordered_map<unsigned int, const std::unordered_set<const PDDLLiteral*>> set;
        for (int i = 0; i < parameters.size(); i++) {
            std::unordered_set<const PDDLLiteral*> tempSet;
            for (int literalIndex = 0; literalIndex < preconditions.size(); literalIndex++) {
                auto literal = &preconditions.at(literalIndex);
                if (literal->args.size() != 1)
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
