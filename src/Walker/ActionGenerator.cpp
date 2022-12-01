#include "ActionGenerator.hpp"

using namespace std;

vector<PDDL::ActionInstance> ActionGenerator::GenerateActions(const PDDL::State *state) {
    vector<PDDL::ActionInstance> legalActions;
    
    unsigned int startI = rand() % actions->size();
    for (int i = 0; i < actions->size(); i++) {
        expansionActionsGenerated = 0;
        unsigned int wI = (startI + i) % actions->size();
        vector<PDDL::ActionInstance> tempActions = GenerateActions(&actions->at(wI), state);
        copy(tempActions.begin(), tempActions.end(), back_inserter(legalActions));
    }
    branchingFactors.push_back(legalActions.size());
    totalActions += legalActions.size();
    return legalActions;
}

vector<PDDL::ActionInstance> ActionGenerator::GenerateActions(const PDDL::Action *action, const PDDL::State *state) {
    vector<PDDL::ActionInstance> legalActions;

    // Object which fulfill the unary literals of the action preconditions
    vector<unordered_set<unsigned int>> candidateObjects;
    candidateObjects.reserve(action->parameters.size());
    if (!GetCandidateObjects(candidateObjects, action, state))
        return legalActions;
    
    unordered_map<pair<unsigned int, unsigned int>, unordered_set<pair<unsigned int, unsigned int>>> candidatePairs;
    for (int i = 0; i < action->preconditions.size(); i++) {
        auto precondition = &action->preconditions.at(i);
        if (precondition->args.size() != 2)
            continue;
        
        auto indexPair = make_pair(precondition->args.at(0), precondition->args.at(1));

        auto pairs = unordered_set<pair<unsigned int, unsigned int>>();
        auto indexFirsts = unordered_set<unsigned int>();
        auto indexSecond = unordered_set<unsigned int>();
        for (auto iter = candidateObjects.at(indexPair.first).begin(); iter != candidateObjects.at(indexPair.first).end(); iter++) {
            for (auto iter2 = candidateObjects.at(indexPair.second).begin(); iter2 != candidateObjects.at(indexPair.second).end(); iter2++) {
                auto pair = make_pair(*iter, *iter2);
                if (state->ContainsFact(precondition->predicateIndex, pair) == precondition->value) {
                    pairs.emplace(pair);
                    indexFirsts.emplace(pair.first);
                    indexSecond.emplace(pair.second);
                }
            }
        }
        if (pairs.size() == 0)
            return legalActions;

        if (!candidatePairs.contains(indexPair)) {
            candidatePairs[indexPair] = pairs;
            // Remove those from candidate objects which are not in any pairs
            AlgorithmHelper::Intersect(candidateObjects.at(indexPair.first), indexFirsts);
            AlgorithmHelper::Intersect(candidateObjects.at(indexPair.second), indexSecond);
        } else {
            // This happens if two preconditions have the same index pair, i.e. pre1: ?x, ?y & pre2: ?x, ?y
            // In this case the legal pairs is the intersection between the two
            AlgorithmHelper::Intersect(candidatePairs.at(indexPair), pairs);
        }
    }

    std::vector<std::vector<unsigned int>> candidatePermutations;
    if (candidateObjects.size() == 1) {
        for (auto iter = candidateObjects.at(0).begin(); iter != candidateObjects.at(0).end(); iter++)
            candidatePermutations.push_back({ *iter });
    } else
        candidatePermutations = PermuteAll(candidateObjects, candidatePairs);
        
    for (int i = 0; i < candidatePermutations.size(); i++)
        legalActions.push_back(PDDL::ActionInstance(action, candidatePermutations.at(i)));
 
    return legalActions;
}

bool ActionGenerator::GetCandidateObjects(vector<unordered_set<unsigned int>> &candidateObjects, const PDDL::Action *action, const PDDL::State *state) const {
    const int parameterLength = action->parameters.size();
    for (int i = 0; i < parameterLength; i++) {
        std::unordered_set<unsigned int> tempCandididateObjects = GetCandidateObjects(&action->applicableUnaryLiterals.at(i), state);
        // if some parameter doesn't have any candidate object, the action is not possible
        if (tempCandididateObjects.size() == 0)
            return false;
        candidateObjects.push_back(tempCandididateObjects);
    }
    return true;
}

unordered_set<unsigned int> ActionGenerator::GetCandidateObjects(const unordered_set<const PDDL::Literal*> *literals, const PDDL::State *state) const {
    unordered_set<unsigned int> candidateObjects;

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

void ActionGenerator::RemoveIllegal(std::unordered_set<unsigned int> &set, const std::unordered_set<const PDDL::Literal*> *literals, const PDDL::State *state) {
    for (auto literal = literals->begin(); literal != literals->end(); literal++)
        if ((*literal)->value)
            AlgorithmHelper::Intersect(set, state->unaryFacts.at((*literal)->predicateIndex));
        else
            AlgorithmHelper::Difference(set, state->unaryFacts.at((*literal)->predicateIndex));
}

std::vector<std::vector<unsigned int>> ActionGenerator::PermuteAll(std::vector<std::unordered_set<unsigned int>> candidateObjects, std::unordered_map<std::pair<unsigned int, unsigned int>, std::unordered_set<std::pair<unsigned int, unsigned int>>> candidatePairs) {
    vector<vector<unsigned int>> permutations;
    vector<unsigned int> permutation;
    permutation.reserve(candidateObjects.size());
    for (auto iter = candidateObjects.at(0).begin(); iter != candidateObjects.at(0).end(); iter++) {
        permutation.push_back(*iter);
        Permute(candidateObjects, candidatePairs, &permutations, &permutation);
        permutation.pop_back();
        if (expansionActionsGenerated > maxExpansionFactor)
            break;
    }
    return permutations;
}

void ActionGenerator::Permute(std::vector<std::unordered_set<unsigned int>> &candidateObjects, std::unordered_map<std::pair<unsigned int, unsigned int>, std::unordered_set<std::pair<unsigned int, unsigned int>>> &candidatePairs, std::vector<std::vector<unsigned int>> *permutations, std::vector<unsigned int> *permutation) {
    for (auto iter = candidateObjects.at(permutation->size()).begin(); iter != candidateObjects.at(permutation->size()).end(); iter++) {
        permutation->push_back(*iter);

        bool validPerm = true;
        for (int i = 0; i < permutation->size(); i++) {
            for (int t = 0; t < permutation->size(); t++) {
                if (i != permutation->size() - 1 && t != permutation->size() - 1)
                    continue;
                auto pair = make_pair(i, t);
                if (candidatePairs.contains(pair) && (!candidatePairs.at(pair).contains(make_pair(permutation->at(pair.first), permutation->at(pair.second))))) {
                    validPerm = false;
                    break;
                }
            }
        }

        if (validPerm) {
            if (permutation->size() == candidateObjects.size()) {
                permutations->push_back(*permutation);
                expansionActionsGenerated++;
            } else {
                Permute(candidateObjects, candidatePairs, permutations, permutation);
                if (expansionActionsGenerated > maxExpansionFactor)
                    break;
            }
        }
        permutation->pop_back();
    }
}
