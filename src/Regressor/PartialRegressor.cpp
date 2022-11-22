#include "PartialRegressor.hh"

#include <queue>

Path PartialRegressor::RegressFromState(const PDDLState *state) {
    std::vector<PartialAction> steps;
    std::unordered_set<PDDLState> visitedStates{*state};
    PDDLState tempState = PDDLState(*state);
    for (int i = 0; i < this->depthFunction->GetDepth(); i++) {
        std::vector<PartialAction> partialActions = actionGenerator->ExpandState(&tempState);
        if (partialActions.size() == 0)
            break;
        
        PartialAction *action = nullptr;
        std::unordered_set<PDDLState> predecessorStates;
        action = GetPredecessorStates(&partialActions, predecessorStates);

        if (action == nullptr) {
            SwitchToNonPartial(&partialActions);
            action = GetPredecessorStates(&partialActions, predecessorStates);
        }

        if (predecessorStates.size() == 0)
            break;

        PDDLActionInstance realAction = actionGenerator->ConvertPartialAction(instance, action);

        GetPredecessorState(&tempState, &realAction);

        if (visitedStates.contains(tempState))
            break;
        else {
            visitedStates.emplace(tempState);
            steps.push_back(*action);
        }
    }
    
    return ConvertToPath(steps);
}

PartialAction* PartialRegressor::GetPredecessorStates(std::vector<PartialAction> *actions, std::unordered_set<PDDLState> &states) {
    int iter = rand() % actions->size();
        for (int i = 0; i < actions->size(); i++) {
            int index = ((iter + i) % actions->size());
            auto tempStates = GetPredecessorStates(&actions->at(index));
            if (tempStates.size() > 0) {
                AlgorithmHelper::InsertAll(states, tempStates);
                return &actions->at(index);
            }
        }
    return nullptr;
}

std::unordered_set<PDDLState> PartialRegressor::GetPredecessorStates(const PartialAction *action) {
    std::unordered_set<PDDLState> states;

    for (int i = 0; i < action->action->preconditions.size(); i++) {
        const PDDLLiteral *literal = &action->action->preconditions.at(i);

        // If the literal is static, ignore
        if (instance->domain->staticPredicates.contains(literal->predicateIndex))
            continue;

        // If the literal contains any partial parameters, ignore
        bool containsPartial = false;
        for (int t = 0; t < literal->args.size(); t++) 
            if (action->parameters.at(literal->args.at(t)) == nullptr) {
                containsPartial = true;
                break;
            }
        if (containsPartial)
            continue;

        states.emplace(GeneratePreconditionState(literal));
    }

    return states;
}

PDDLState PartialRegressor::GeneratePreconditionState(const PDDLLiteral *literal) {
    const int argumentCount = literal->args.size();
    if (argumentCount == 1)
        return PDDLState(
            std::unordered_map<unsigned int, std::unordered_set<unsigned int>> { 
                {literal->predicateIndex, std::unordered_set<unsigned int>{ literal->args.at(0) }} 
            },
            std::unordered_map<unsigned int, std::unordered_set<std::pair<unsigned int, unsigned int>>> {}
        );
    else if (argumentCount == 2)
        return PDDLState(
            std::unordered_map<unsigned int, std::unordered_set<unsigned int>> {},
            std::unordered_map<unsigned int, std::unordered_set<std::pair<unsigned int, unsigned int>>> { 
                {literal->predicateIndex, std::unordered_set<std::pair<unsigned int, unsigned int>>{ std::make_pair(literal->args.at(0), literal->args.at(1)) }} 
            }
        );
    else 
        return PDDLState(
            std::unordered_map<unsigned int, std::unordered_set<unsigned int>> {},
            std::unordered_map<unsigned int, std::unordered_set<std::pair<unsigned int, unsigned int>>> {}
        );
}

void PartialRegressor::GetPredecessorState(PDDLState *state, const PDDLActionInstance *action) {
    // Handle effects
    // Assumes that positive effects were untrue before action
    for (int i = 0; i < action->action->effects.size(); i++) {
        auto effect = &action->action->effects.at(i);
        if (effect->args.size() == 1) {
            if (effect->value)
                state->unaryFacts.at(effect->predicateIndex).erase(action->objects.at(effect->args.at(0)));
            else
                state->unaryFacts.at(effect->predicateIndex).emplace(action->objects.at(effect->args.at(0)));
        } else {
            if (effect->value)
                state->binaryFacts.at(effect->predicateIndex).erase(std::make_pair(action->objects.at(effect->args.at(0)), action->objects.at(effect->args.at(1))));
            else
                state->binaryFacts.at(effect->predicateIndex).emplace(std::make_pair(action->objects.at(effect->args.at(0)), action->objects.at(effect->args.at(1))));
        }
    }

    // Handle preconditions
    for (int i = 0; i < action->action->preconditions.size(); i++) {
        auto precondition = &action->action->preconditions.at(i);
        if (precondition->args.size() == 1) {
            if (precondition->value)
                state->unaryFacts.at(precondition->predicateIndex).emplace(action->objects.at(precondition->args.at(0)));
            else
                state->unaryFacts.at(precondition->predicateIndex).erase(action->objects.at(precondition->args.at(0)));
        } else {
            if (precondition->value)
                state->binaryFacts.at(precondition->predicateIndex).emplace(std::make_pair(action->objects.at(precondition->args.at(0)), action->objects.at(precondition->args.at(1))));
            else
                state->binaryFacts.at(precondition->predicateIndex).erase(std::make_pair(action->objects.at(precondition->args.at(0)), action->objects.at(precondition->args.at(1))));
        }
    }
}

void PartialRegressor::SwitchToNonPartial(std::vector<PartialAction> *actions) {
    for (int i = 0; i < actions->size(); i++)
        actionGenerator->FillPartialAction(instance, &actions->at(i));
}

Path PartialRegressor::ConvertToPath(std::vector<PartialAction> actions) {
    std::vector<PDDLActionInstance> steps;
    for (int i = 0; i < actions.size(); i++)
        steps.push_back(actionGenerator->ConvertPartialAction(instance, &actions.at(i)));
    return Path(steps);
}
