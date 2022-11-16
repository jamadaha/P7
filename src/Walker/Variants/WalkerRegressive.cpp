#include "WalkerRegressive.hpp"

Path WalkerRegressive::Walk(BaseHeuristic *heuristic, const PDDLState *state) {
    std::vector<PDDLActionInstance> steps; steps.reserve(maxStepCount);
    std::unordered_set<PDDLState> visitedStates; visitedStates.reserve(maxStepCount);

    PDDLState tempState = instance->problem->goalState;
    if (OnTempStateMade != nullptr)
        OnTempStateMade(this->instance, &tempState);

    for (int i = 0; i < maxStepCount; i++) {
        std::vector<PDDLActionInstance> possibleActions;
        possibleActions = actionGenerator->GenerateActions(&tempState);

        if (possibleActions.size() == 0) break;
        PDDLActionInstance *chosenAction = heuristic->NextChoice(&tempState, &possibleActions);
        DoRegressiveAction(&tempState, chosenAction);

        if (visitedStates.contains(tempState))
            break;
        else {
            visitedStates.emplace(tempState);
            steps.push_back(*chosenAction);

            if (OnStateWalk != nullptr)
                OnStateWalk(this->instance, &tempState, chosenAction);
        }
    }

    std::reverse(steps.begin(), steps.end());
    return Path(steps);
}

std::vector<Path> WalkerRegressive::Walk() {
    std::vector<Path> paths;
    unsigned int current;
    if (OnWalkerStart != nullptr)
        OnWalkerStart(this);
    auto startTime = std::chrono::steady_clock::now();
    while (widthFunc->Iterate(&current)) {
        Path path = Walk(heuristic, &this->instance->problem->initState);
        paths.push_back(path);

        if (OnWalkerStep != nullptr)
            OnWalkerStep(this, current);
        _totalIterations++;
    }
    auto ellapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - startTime).count();
    if (OnWalkerEnd != nullptr)
        OnWalkerEnd(this, ellapsed);
    return paths;
}

void WalkerRegressive::DoRegressiveAction(PDDLState *state, const PDDLActionInstance *action) {
    for (int i = 0; i < action->action->preconditions.size(); i++) {
        auto precon = &action->action->preconditions.at(i);
        if (!instance->domain->staticPredicates.contains(precon->predicateIndex)) {
            if (precon->args.size() == 1)
                state->unaryFacts.at(precon->predicateIndex).emplace(action->objects.at(precon->args.at(0)));
            else
                state->binaryFacts.at(precon->predicateIndex).emplace(
                    std::make_pair(action->objects.at(precon->args.at(0)), action->objects.at(precon->args.at(1)))
                );
        }
    }
    state->UndoAction(action);
}