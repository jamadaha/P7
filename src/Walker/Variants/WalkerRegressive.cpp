#include "WalkerRegressive.hpp"

#include "../../Helpers/AlgorithmHelper.hh"

std::vector<Path> WalkerRegressive::Walk(BaseHeuristic *heuristic, const PDDLState *state) {
    std::vector<Path> paths;
    std::vector<PDDLActionInstance> steps; steps.reserve(maxStepCount);

    PDDLState tempState = instance->problem->goalState;
    if (OnTempStateMade != nullptr)
        OnTempStateMade(this->instance, &tempState);

    std::unordered_set<PDDLState> visitedStates; visitedStates.reserve(maxStepCount);
    std::vector<std::pair<std::vector<PDDLActionInstance>, PDDLState>> searchStack; searchStack.reserve(maxStepCount);
    searchStack.push_back(std::make_pair(steps, tempState));

    for (int i = 0; i < maxStepCount && searchStack.size() > 0; i++) {
        auto searchNode = searchStack.at(searchStack.size() - 1); 
        searchStack.pop_back();

        if (visitedStates.contains(searchNode.second)) { 
            if (searchNode.first.size() > 0) {
                std::reverse(searchNode.first.begin(), searchNode.first.end());
                paths.push_back(Path(searchNode.first));
            }
            continue;
        }
        else visitedStates.emplace(searchNode.second);

        std::vector<PDDLActionInstance> possibleActions = actionGenerator->GenerateActions(&searchNode.second);
        if (possibleActions.size() == 0) continue;

        for (int i = 0; i < possibleActions.size(); i++) {
            auto action = &possibleActions.at(i);
            auto resultState = DoRegressiveAction(&searchNode.second, action);
            searchNode.first.push_back(*action);
            searchStack.push_back(std::make_pair(searchNode.first, resultState));
            searchNode.first.pop_back();
        }
    }

    std::reverse(steps.begin(), steps.end());
    paths.push_back(Path(steps));
    return paths;
}

std::vector<Path> WalkerRegressive::Walk() {
    std::vector<Path> paths;
    unsigned int current;
    if (OnWalkerStart != nullptr)
        OnWalkerStart(this);
    auto startTime = std::chrono::steady_clock::now();
    while (widthFunc->Iterate(&current)) {
        AlgorithmHelper::InsertAll(paths, Walk(heuristic, &this->instance->problem->initState));

        if (OnWalkerStep != nullptr)
            OnWalkerStep(this, current);
        _totalIterations++;
    }
    auto ellapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - startTime).count();
    if (OnWalkerEnd != nullptr)
        OnWalkerEnd(this, ellapsed);
    return paths;
}

PDDLState WalkerRegressive::DoRegressiveAction(const PDDLState *state, const PDDLActionInstance *action) {
    PDDLState tempState = PDDLState(*state);
    for (int i = 0; i < action->action->preconditions.size(); i++) {
        auto precon = &action->action->preconditions.at(i);
        if (!instance->domain->staticPredicates.contains(precon->predicateIndex)) {
            if (precon->args.size() == 1)
                tempState.unaryFacts.at(precon->predicateIndex).emplace(action->objects.at(precon->args.at(0)));
            else
                tempState.binaryFacts.at(precon->predicateIndex).emplace(
                    std::make_pair(action->objects.at(precon->args.at(0)), action->objects.at(precon->args.at(1)))
                );
        }
    }
    tempState.UndoAction(action);
    return tempState;
}