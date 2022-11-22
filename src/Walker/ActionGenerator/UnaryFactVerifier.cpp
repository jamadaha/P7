#include "UnaryFactVerifier.hpp"

std::vector<std::unordered_set<unsigned int>> UnaryFactVerifier::GetLegalObjects(const PDDLAction *action, const PDDLState *state) const {
    const int parameterLength = action->parameters.size();
    std::vector<std::unordered_set<unsigned int>> legalObjects;
    legalObjects.reserve(parameterLength);

    for (int i = 0; i < parameterLength; i++) {
        std::unordered_set<unsigned int> tempCandididateObjects = 
            GetLegalObjectsForParameter(&action->applicableUnaryLiterals.at(i), state);
        // if some parameter doesn't have any legal object, the action is not possible
        if (tempCandididateObjects.size() == 0)
            return legalObjects;
        legalObjects.push_back(tempCandididateObjects);
    }
    return std::vector<std::unordered_set<unsigned int>>();
}

std::unordered_set<unsigned int> UnaryFactVerifier::GetLegalObjectsForParameter(    const std::unordered_set<const PDDLLiteral*> *literals, 
                                                                                    const PDDLState *state) const 
{
    std::unordered_set<unsigned int> candidateObjects;

    for (auto iter = literals->begin(); iter != literals->end(); iter++)
        if ((*iter)->value == true) {
            candidateObjects = state->unaryFacts.at((*iter)->predicateIndex);
            break;
        }

    if (candidateObjects.size() == 0)
        candidateObjects = objects;
    
    RemoveIllegal(candidateObjects, literals, state);

    return candidateObjects;
}

void UnaryFactVerifier::RemoveIllegal(  std::unordered_set<unsigned int> &set, 
                                        const std::unordered_set<const PDDLLiteral*> *literals, 
                                        const PDDLState *state)
{
    for (auto literal = literals->begin(); literal != literals->end(); literal++)
        if ((*literal)->value)
            AlgorithmHelper::Intersect(set, state->unaryFacts.at((*literal)->predicateIndex));
        else
            AlgorithmHelper::Difference(set, state->unaryFacts.at((*literal)->predicateIndex));
}