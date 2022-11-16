#include "ActionGeneratorRegressing.hpp"

#include "../../Helpers/AlgorithmHelper.hh"

using namespace std;

PDDLActionInstance ActionGeneratorRegressing::GenerateRandomAction(const PDDLState *state) {
    throw std::logic_error("Not implemented");
}

vector<PDDLActionInstance> ActionGeneratorRegressing::GenerateActions(const PDDLState *state) {
    vector<PDDLActionInstance> legalActions;

    for (auto iter = state->unaryFacts.begin(); iter != state->unaryFacts.end(); iter++) {
        auto facts = &(*iter).second;
        for (auto factIter = facts->begin(); factIter != facts->end(); factIter++)
            AlgorithmHelper::InsertAll(legalActions, GenerateActionsFromUnary(state, (*iter).first, *factIter));
    }

    for (auto iter = state->binaryFacts.begin(); iter != state->binaryFacts.end(); iter++) {
        auto facts = &(*iter).second;
        for (auto factIter = facts->begin(); factIter != facts->end(); factIter++)
            AlgorithmHelper::InsertAll(legalActions, GenerateActionsFromBinary(state, (*iter).first, *factIter));
    }

    totalActions += legalActions.size();
    return legalActions;
}

std::vector<PDDLActionInstance> ActionGeneratorRegressing::GenerateActionsFromUnary(const PDDLState *state, const unsigned int predicate, const unsigned int object) {
    std::vector<PDDLActionInstance> actions;
    auto applicableActions = &instance->domain->predicateActions.at(predicate);

    for (auto iter = applicableActions->begin(); iter != applicableActions->end(); iter++) {
        auto action = *iter;
        auto effects = &action->effects;
        // Get which efffect is relevant
        for (int i = 0; i < effects->size(); i++) {
            auto effect = &effects->at(i);
            if (predicate == effect->predicateIndex && effect->value) {
                AlgorithmHelper::InsertAll(actions, GenerateFromPartial(state, action, { { effect->args.at(0), object } }));
                break;
            }
        }
        
    }

    return actions;
}

std::vector<PDDLActionInstance> ActionGeneratorRegressing::GenerateActionsFromBinary(const PDDLState *state, const unsigned int predicate, const std::pair<unsigned int, unsigned int> objects) {
    std::vector<PDDLActionInstance> actions;
    auto applicableActions = &instance->domain->predicateActions.at(predicate);

    for (auto iter = applicableActions->begin(); iter != applicableActions->end(); iter++) {
        auto action = *iter;
        auto effects = &action->effects;
        // Get which efffect is relevant
        for (int i = 0; i < effects->size(); i++) {
            auto effect = &effects->at(i);
            if (predicate == effect->predicateIndex && effect->value) {
                AlgorithmHelper::InsertAll(actions, GenerateFromPartial(state, action, { { effect->args.at(0), objects.first }, { effect->args.at(1), objects.second } }));
                break;
            }
        }
        
    }

    return actions;
}

std::vector<PDDLActionInstance> ActionGeneratorRegressing::GenerateFromPartial(const PDDLState *state, const PDDLAction *action, const std::map<unsigned int, unsigned int> partialParameters) {
    std::vector<unordered_set<unsigned int>> candidateObjects;
    for (unsigned int i = 0; i < action->parameters.size(); i++) {
        if (!partialParameters.contains(i))
            candidateObjects.push_back(GetCandidateObjects(state, action, &i));
        else
            candidateObjects.push_back({ partialParameters.at(i) });
    }

    auto legalPairings = GenerateLegalPairings(state, action, &candidateObjects);
    auto permutations = PermuteAll(&candidateObjects, &legalPairings);
    std::vector<PDDLActionInstance> actionInstances; actionInstances.reserve(permutations.size());
    for (int i = 0; i < permutations.size(); i++) {
        auto permutation = &permutations.at(i);
        actionInstances.push_back(PDDLActionInstance(action, *permutation));
    }
    return actionInstances;
}

std::unordered_set<unsigned int> ActionGeneratorRegressing::GetCandidateObjects(const PDDLState *state, const PDDLAction *action, const unsigned int *index) {
    std::unordered_set<unsigned int> objects;
    const PDDLLiteral* staticLiteral = IsParamStatic(action, index);
    if (staticLiteral != nullptr) {
        auto clusterRef = action->preClusterMembership.at(*index);
        if (clusterRef == nullptr || clusterRef->size() == 2) {
            if (state->unaryFacts.at(staticLiteral->predicateIndex).size() == 0)
                for (auto iter = instance->problem->initState.unaryFacts.at(staticLiteral->predicateIndex).begin(); iter != instance->problem->initState.unaryFacts.at(staticLiteral->predicateIndex).end(); iter++)
                    objects.emplace(*iter);
            else
                for (auto iter = state->unaryFacts.at(staticLiteral->predicateIndex).begin(); iter != state->unaryFacts.at(staticLiteral->predicateIndex).end(); iter++)
                    objects.emplace(*iter);
        } else {
            throw std::logic_error("Not implemented");
        }
    } else {
        throw std::logic_error("Not implemented");
    }

    return objects;
}

const PDDLLiteral* ActionGeneratorRegressing::IsParamStatic(const PDDLAction *action, const unsigned int *index) {
    int isStatic = -1;

    for (auto iter = action->applicableUnaryLiterals.at(*index).begin(); iter != action->applicableUnaryLiterals.at(*index).end(); iter++)
        if (instance->domain->staticPredicates.contains((*iter)->predicateIndex))
            return *iter;
    
    for (auto iter = action->applicableMultiLiterals.at(*index).begin(); iter != action->applicableMultiLiterals.at(*index).end(); iter++)
        if (instance->domain->staticPredicates.contains((*iter)->predicateIndex))
            return *iter;

    return nullptr;
}


std::unordered_map<std::pair<unsigned int, unsigned int>, std::unordered_set<std::pair<unsigned int, unsigned int>>> 
ActionGeneratorRegressing::GenerateLegalPairings(const PDDLState *state, const PDDLAction *action, std::vector<std::unordered_set<unsigned int>> *candidateObjects) {
    unordered_map<pair<unsigned int, unsigned int>, unordered_set<pair<unsigned int, unsigned int>>> candidatePairs;
    for (int i = 0; i < action->preconditions.size(); i++) {
        auto precondition = &action->preconditions.at(i);
        if (precondition->args.size() != 2)
            continue;
        
        auto indexPair = make_pair(precondition->args.at(0), precondition->args.at(1));

        auto pairs = unordered_set<pair<unsigned int, unsigned int>>();
        auto indexFirsts = unordered_set<unsigned int>();
        auto indexSecond = unordered_set<unsigned int>();
        for (auto iter = candidateObjects->at(indexPair.first).begin(); iter != candidateObjects->at(indexPair.first).end(); iter++) {
            for (auto iter2 = candidateObjects->at(indexPair.second).begin(); iter2 != candidateObjects->at(indexPair.second).end(); iter2++) {
                auto pair = make_pair(*iter, *iter2);
                if (precondition->predicateIndex != 0 || ((pair.first == pair.second) == precondition->value)) {
                    pairs.emplace(pair);
                    indexFirsts.emplace(pair.first);
                    indexSecond.emplace(pair.second);
                }
            }
        }
        if (pairs.size() == 0)
            return candidatePairs;

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
