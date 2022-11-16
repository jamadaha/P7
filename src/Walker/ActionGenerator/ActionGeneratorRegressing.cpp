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

    auto permutations = PermuteAll(&candidateObjects);
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
            for (auto iter = instance->problem->initState.unaryFacts.at(staticLiteral->predicateIndex).begin(); iter != instance->problem->initState.unaryFacts.at(staticLiteral->predicateIndex).end(); iter++)
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

std::vector<std::vector<unsigned int>> ActionGeneratorRegressing::PermuteAll(const std::vector<std::unordered_set<unsigned int>> *objects) {
    vector<vector<unsigned int>> permutations;
    vector<unsigned int> permutation; permutation.reserve(objects->size());
    for (auto iter = objects->at(0).begin(); iter != objects->at(0).end(); iter++) {
        permutation.push_back(*iter);
        Permute(objects, &permutations, &permutation);
        permutation.pop_back();
    }
    return permutations;
}

void ActionGeneratorRegressing::Permute(const std::vector<std::unordered_set<unsigned int>> *objects, std::vector<std::vector<unsigned int>> *permutations, std::vector<unsigned int> *permutation) {
    for (auto iter = objects->at(permutation->size()).begin(); iter != objects->at(permutation->size()).end(); iter++) {
        permutation->push_back(*iter);

        if (permutation->size() == objects->size())
            permutations->push_back(*permutation);
        else
            Permute(objects, permutations, permutation);

        permutation->pop_back();
    }
}
