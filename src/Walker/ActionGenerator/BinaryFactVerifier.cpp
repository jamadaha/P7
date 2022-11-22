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

        auto pairs = std::unordered_set<std::pair<unsigned int, unsigned int>>();
        auto indexFirsts = std::unordered_set<unsigned int>();
        auto indexSecond = std::unordered_set<unsigned int>();
        for (auto iter = candidateObjects->at(indexPair.first).begin(); iter != candidateObjects->at(indexPair.first).end(); iter++) {
            for (auto iter2 = candidateObjects->at(indexPair.second).begin(); iter2 != candidateObjects->at(indexPair.second).end(); iter2++) {
                auto pair = std::make_pair(*iter, *iter2);
                if (state->ContainsFact(precondition->predicateIndex, pair) == precondition->value) {
                    pairs.emplace(pair);
                    indexFirsts.emplace(pair.first);
                    indexSecond.emplace(pair.second);
                }
            }
        }

        if (!candidatePairs.contains(indexPair)) {
            candidatePairs[indexPair] = pairs;
            // Remove those from candidate objects which are not in any pairs
            AlgorithmHelper::Intersect(candidateObjects->at(indexPair.first), indexFirsts);
            AlgorithmHelper::Intersect(candidateObjects->at(indexPair.second), indexSecond);
        } else {
            // This happens if two preconditions have the same index pair, i.e. pre1: ?x, ?y & pre2: ?x, ?y
            // In this case the legal pairs is the intersection between the two
            AlgorithmHelper::Intersect(candidatePairs.at(indexPair), pairs);
        }
    }
    return candidatePairs;
}