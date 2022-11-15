#include "ActionGeneratorRegressing.hpp"

#include "../../Helpers/AlgorithmHelper.hh"

using namespace std;

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
            if (predicate == effect->predicateIndex) {
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
            if (predicate == effect->predicateIndex) {
                AlgorithmHelper::InsertAll(actions, GenerateFromPartial(state, action, { { effect->args.at(0), objects.first }, { effect->args.at(1), objects.second } }));
                break;
            }
        }
        
    }

    return actions;
}

std::vector<PDDLActionInstance> ActionGeneratorRegressing::GenerateFromPartial(const PDDLState *state, const PDDLAction *action, const std::unordered_map<unsigned int, unsigned int> partialParameters) {
    printf("\n");
}
