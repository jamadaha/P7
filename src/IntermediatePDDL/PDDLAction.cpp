#include "PDDLAction.hh"

std::size_t PDDLAction::GetHash() {
    if (HashValue != 0)
        return HashValue;
    HashValue = std::hash<PDDLAction*>{}(this);
    return HashValue;
}

std::vector<std::unordered_set<const PDDLLiteral*>> PDDLAction::GenerateApplicableLiterals(bool unary) const {
    std::vector<std::unordered_set<const PDDLLiteral*>> set;
    if (parameters.size() == 0 || preconditions.size() == 0)
        return set;
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
        set.push_back(tempSet);
    }
    return set;
};

std::vector<std::unordered_set<unsigned int>> PDDLAction::GenerateApplicablePredicates(bool unary) const {
    std::vector<std::unordered_set<unsigned int>> set;
    if (parameters.size() == 0)
        return set;
    for (int i = 0; i < parameters.size(); i++) {
        std::unordered_set<unsigned int> tempSet;
        
        for (auto literal : applicableUnaryLiterals.at(i)) {
            tempSet.emplace(literal->predicateIndex);
        }
        set.push_back(tempSet);
    }
    return set;
};
