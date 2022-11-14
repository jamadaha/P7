#include "PartialRegressor.hh"

#include <queue>

Path PartialRegressor::Regress(const PDDLState *state) {
    std::vector<PartialAction> steps;
    std::unordered_set<PDDLState> visitedStates{*state};
    PDDLState tempState = PDDLState(*state);
    for (int i = 0; i < 100; i++) {
        std::unordered_set<PartialAction> partialActions = actionGenerator->ExpandState(&tempState);
        if (partialActions.size() == 0)
            break;
        
        const PartialAction *chosenAction = &*std::next(partialActions.begin(), rand() % partialActions.size());

        std::unordered_set<PDDLState> predecessorStates = GetPredecessorStates(&*partialActions.begin());
        if (predecessorStates.size() == 0)
            break;

        tempState = *std::next(predecessorStates.begin(), rand() % predecessorStates.size());

        if (visitedStates.contains(tempState))
            break;
        else {
            visitedStates.emplace(tempState);
            steps.push_back(*chosenAction);
        }
    }
    
    return ConvertToPath(steps);
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
            std::unordered_map<unsigned int, std::unordered_set<std::pair<unsigned int, unsigned int>>> {},
            std::unordered_map<unsigned int, std::unordered_set<MultiFact>> {}
        );
    else if (argumentCount == 2)
        return PDDLState(
            std::unordered_map<unsigned int, std::unordered_set<unsigned int>> {},
            std::unordered_map<unsigned int, std::unordered_set<std::pair<unsigned int, unsigned int>>> { 
                {literal->predicateIndex, std::unordered_set<std::pair<unsigned int, unsigned int>>{ std::make_pair(literal->args.at(0), literal->args.at(1)) }} 
            },
            std::unordered_map<unsigned int, std::unordered_set<MultiFact>> {}
        );
    else 
        return PDDLState(
            std::unordered_map<unsigned int, std::unordered_set<unsigned int>> {},
            std::unordered_map<unsigned int, std::unordered_set<std::pair<unsigned int, unsigned int>>> {},
            std::unordered_map<unsigned int, std::unordered_set<MultiFact>> {
                {literal->predicateIndex, std::unordered_set<MultiFact>{ MultiFact(literal->args) }}
            }
        );
}

Path PartialRegressor::ConvertToPath(std::vector<PartialAction> actions) {
    std::vector<PDDLActionInstance> steps;
    for (int i = 0; i < actions.size(); i++)
        steps.push_back(actionGenerator->FillPartialAction(instance, &actions.at(i)));
    return Path(steps);
}
