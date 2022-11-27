#include "PartialRegressor.hh"

#include <queue>

Path PartialRegressor::RegressFromState(const PDDL::State *state) {
    std::vector<PartialAction> steps;
    std::unordered_set<PDDL::State> visitedStates{*state};
    PDDL::State tempState = PDDL::State(*state);
    for (int i = 0; i < this->depthFunction->GetDepth(); i++) {
        std::vector<PartialAction> partialActions = actionGenerator->ExpandState(&tempState);
        if (partialActions.size() == 0)
            break;
        
        PartialAction *action = nullptr;
        std::unordered_set<PDDL::State> predecessorStates;
        action = GetPredecessorStates(&partialActions, predecessorStates);

        if (action == nullptr) {
            SwitchToNonPartial(&partialActions);
            action = GetPredecessorStates(&partialActions, predecessorStates);
        }

        if (predecessorStates.size() == 0)
            break;

        PDDL::ActionInstance realAction = actionGenerator->ConvertPartialAction(instance, action);

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

PartialAction* PartialRegressor::GetPredecessorStates(std::vector<PartialAction> *actions, std::unordered_set<PDDL::State> &states) {
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

std::unordered_set<PDDL::State> PartialRegressor::GetPredecessorStates(const PartialAction *action) {
    std::unordered_set<PDDL::State> states;

    for (int i = 0; i < action->action->preconditions.size(); i++) {
        const PDDL::Literal *literal = &action->action->preconditions.at(i);

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

PDDL::State PartialRegressor::GeneratePreconditionState(const PDDL::Literal *literal) {
    const int argumentCount = literal->args.size();
    if (argumentCount == 1)
        return PDDL::State(
            std::unordered_map<unsigned int, std::unordered_set<unsigned int>> { 
                {literal->predicateIndex, std::unordered_set<unsigned int>{ literal->args.at(0) }} 
            },
            std::unordered_map<unsigned int, std::unordered_set<std::pair<unsigned int, unsigned int>>> {}
        );
    else if (argumentCount == 2)
        return PDDL::State(
            std::unordered_map<unsigned int, std::unordered_set<unsigned int>> {},
            std::unordered_map<unsigned int, std::unordered_set<std::pair<unsigned int, unsigned int>>> { 
                {literal->predicateIndex, std::unordered_set<std::pair<unsigned int, unsigned int>>{ std::make_pair(literal->args.at(0), literal->args.at(1)) }} 
            }
        );
    else 
        return PDDL::State(
            std::unordered_map<unsigned int, std::unordered_set<unsigned int>> {},
            std::unordered_map<unsigned int, std::unordered_set<std::pair<unsigned int, unsigned int>>> {}
        );
}

void PartialRegressor::SwitchToNonPartial(std::vector<PartialAction> *actions) {
    for (int i = 0; i < actions->size(); i++)
        actionGenerator->FillPartialAction(instance, &actions->at(i));
}

Path PartialRegressor::ConvertToPath(std::vector<PartialAction> actions) {
    std::vector<PDDL::ActionInstance> steps;
    for (int i = 0; i < actions.size(); i++)
        steps.push_back(actionGenerator->ConvertPartialAction(instance, &actions.at(i)));
    return Path(steps);
}
