#include "BinaryFactVerifier.hpp"

std::unordered_map<std::pair<unsigned int, unsigned int>, std::unordered_set<std::pair<unsigned int, unsigned int>>>
        BinaryFactVerifier::GetLegalPairings(   const PDDLAction* action, const PDDLState *state,
                            std::vector<std::unordered_set<unsigned int>> *candidateObjects)
{
    std::unordered_map<std::pair<unsigned int, unsigned int>, std::unordered_set<std::pair<unsigned int, unsigned int>>> candidatePairs;
    for (int i = 0; i < action->preconditions.size(); i++) {
        auto precondition = &action->preconditions.at(i);
        if (precondition->args.size() != 2)
            continue;
        
        auto indexPair = std::make_pair(precondition->args.at(0), precondition->args.at(1));
        auto legalPairInfo = GenerateLegalPairings(precondition, state, candidateObjects, &indexPair);
        UpdateCandidateObjects(&indexPair, candidateObjects, &legalPairInfo);
        UpdateLegalPairings(&indexPair, &candidatePairs, &legalPairInfo);
    }
    return candidatePairs;
}

LegalPairInformation BinaryFactVerifier::GenerateLegalPairings( const PDDLLiteral* precondition,
                                                                const PDDLState *state,
                                                                const std::vector<std::unordered_set<unsigned int>> *candidateObjects,
                                                                const std::pair<unsigned int, unsigned int> *indexPair) 
{
    auto legalPairInformation = LegalPairInformation();

    for (auto iter = candidateObjects->at(indexPair->first).begin(); iter != candidateObjects->at(indexPair->first).end(); iter++) {
        for (auto iter2 = candidateObjects->at(indexPair->second).begin(); iter2 != candidateObjects->at(indexPair->second).end(); iter2++) {
            auto pair = std::make_pair(*iter, *iter2);
            if (state->ContainsFact(precondition->predicateIndex, pair) == precondition->value) {
                legalPairInformation.pairs.emplace(pair);
                legalPairInformation.indexFirst.emplace(pair.first);
                legalPairInformation.indexSecond.emplace(pair.second);
            }
        }
    }
    return legalPairInformation;
}

void BinaryFactVerifier::UpdateCandidateObjects(const std::pair<unsigned int, unsigned int> *indexPair, 
                                                std::vector<std::unordered_set<unsigned int>> *candidateObjects,
                                                const LegalPairInformation *newInformation) 
{
    // Remove those from candidate objects which are not in any pairs
    AlgorithmHelper::Intersect(candidateObjects->at(indexPair->first), newInformation->indexFirst);
    AlgorithmHelper::Intersect(candidateObjects->at(indexPair->second), newInformation->indexSecond);
}

void BinaryFactVerifier::UpdateLegalPairings(
    const std::pair<unsigned int, unsigned int> *indexPair,
    std::unordered_map<std::pair<unsigned int, unsigned int>, std::unordered_set<std::pair<unsigned int, unsigned int>>> *candidatePairs,
    const LegalPairInformation *newInformation) 
{
    if (!candidatePairs->contains(*indexPair)) {
        if (!candidatePairs->contains(*indexPair))
            candidatePairs->emplace(*indexPair, newInformation->pairs);
        else
            candidatePairs->at(*indexPair) = newInformation->pairs;
    } else {
        // This happens if two preconditions have the same index pair, i.e. pre1: ?x, ?y & pre2: ?x, ?y
        // In this case the legal pairs is the intersection between the two
        AlgorithmHelper::Intersect(candidatePairs->at(*indexPair), newInformation->pairs);
    }
}