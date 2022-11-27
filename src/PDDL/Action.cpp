#include "Action.hh"

using namespace std;
using namespace PDDL;

vector<unordered_set<const Literal*>> Action::GenerateApplicableLiterals(bool unary) const {
    vector<unordered_set<const Literal*>> set;
    if (parameters.size() == 0 || preconditions.size() == 0)
        return set;
    for (int i = 0; i < parameters.size(); i++) {
        unordered_set<const Literal*> tempSet;
        for (int literalIndex = 0; literalIndex < preconditions.size(); literalIndex++) {
            const Literal *literal = &preconditions.at(literalIndex);
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

vector<unordered_set<unsigned int>> Action::GenerateApplicablePredicates() const {
    vector<unordered_set<unsigned int>> set;
    if (parameters.size() == 0 || preconditions.size() == 0)
        return set;
    for (int i = 0; i < parameters.size(); i++) {
        unordered_set<unsigned int> tempSet;
        
        for (auto literal : applicableUnaryLiterals.at(i)) {
            tempSet.emplace(literal->predicateIndex);
        }
        set.push_back(tempSet);
    }
    return set;
};

vector<unordered_set<unsigned int>> Action::GenerateApplicablePredicates(bool unary) const {
    vector<unordered_set<unsigned int>> set;
    if (parameters.size() == 0 || preconditions.size() == 0)
        return set;
    for (int i = 0; i < parameters.size(); i++) {
        unordered_set<unsigned int> tempSet;
        
        for (auto literal : applicableUnaryLiterals.at(i)) {
            tempSet.emplace(literal->predicateIndex);
        }
        set.push_back(tempSet);
    }
    return set;
};
