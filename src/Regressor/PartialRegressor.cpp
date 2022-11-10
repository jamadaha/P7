#include "PartialRegressor.hh"

#include <queue>

std::vector<Path> PartialRegressor::Regress(const PDDLState *state) {
    std::unordered_set<PDDLState> visitedStates{*state};
    PartialActionGenerator actionGenerator = PartialActionGenerator(&instance->domain->actions, instance->problem->objects.size());
    PDDLState tempState = PDDLState(*state);
    for (int i = 0; i < 100; i++) {
        std::unordered_set<PartialAction> partialActions = actionGenerator.ExpandState(&tempState);
        if (partialActions.size() == 0)
            continue;
        std::unordered_set<PDDLState> predecessorStates = GetPredecessorStates(&*partialActions.begin());
        tempState = *predecessorStates.begin();
    }
    
    printf("\n");
}

std::unordered_set<PDDLState> PartialRegressor::GetPredecessorStates(const PartialAction *action) {
    std::unordered_set<PDDLState> states;

    for (int i = 0; i < action->action->preconditions.size(); i++) {
        const PDDLLiteral *literal = &action->action->preconditions.at(i);

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