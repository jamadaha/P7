#include "WalkerGreedyResume.hpp"

Path WalkerGreedyResume::Walk(BaseHeuristic *heuristic, const PDDLState *state) {
    std::vector<PDDLActionInstance> steps; steps.reserve(maxStepCount);
    std::unordered_set<PDDLState> visitedStates; visitedStates.reserve(maxStepCount);

    PDDLState tempState = PDDLState(state->unaryFacts, state->binaryFacts);
    if (OnTempStateMade != nullptr)
        OnTempStateMade(this->instance, &tempState);

    for (int i = 0; i < maxStepCount; i++) {
        std::vector<PDDLActionInstance> possibleActions;
        possibleActions = actionGenerator.GenerateActions(&tempState);

        if (possibleActions.size() == 0) break;
        PDDLActionInstance *chosenAction = heuristic->NextChoice(&tempState, &possibleActions);
        tempState.DoAction(chosenAction);

        if (visitedStates.contains(tempState))
            break;
        else {
            visitedStates.emplace(tempState);
            steps.push_back(*chosenAction);
            int value = heuristic->Eval(&tempState); 
            if (value > bestValue) {
                bestState = tempState;
                bestValue = value;
            }


            if (OnStateWalk != nullptr)
                OnStateWalk(this->instance, &tempState, chosenAction);
        }
    }

    return Path(steps);
}

std::vector<Path> WalkerGreedyResume::Walk() {
    std::vector<Path> paths;
    unsigned int current;
    if (OnWalkerStart != nullptr)
        OnWalkerStart(this);
    bestState = this->instance->problem->initState;
    bestValue = 0;
    auto startTime = std::chrono::steady_clock::now();
    while (widthFunc->Iterate(&current)) {
        Path path = Walk(heuristic, &bestState);
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