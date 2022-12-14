#include "WalkerGreedyResume.hpp"

Path WalkerGreedyResume::Walk(BaseHeuristic *heuristic, const PDDL::State state, unsigned int* current) {
    std::vector<PDDL::ActionInstance> steps; 
    steps.reserve(maxStepCount);
    std::unordered_set<PDDL::State> visitedStates; 
    visitedStates.reserve(maxStepCount);

    PDDL::State tempState = PDDL::State(state.unaryFacts, state.binaryFacts);
    visitedStates.emplace(tempState);
    PDDL::State endState;
    if (OnTempStateMade != nullptr)
        OnTempStateMade(this->instance, &tempState);

    heuristic->Reset();

    for (int i = 0; i < maxStepCount; i++) {
        if (!widthFunc->Iterate(current))
            break;

        std::vector<PDDL::ActionInstance> possibleActions;
        possibleActions = actionGenerator.GenerateActions(&tempState);

        if (possibleActions.size() == 0) break;
        PDDL::ActionInstance *chosenAction = heuristic->NextChoice(&tempState, &possibleActions);
        tempState.DoAction(chosenAction);

        if (visitedStates.contains(tempState))
            break;
        else {
            visitedStates.emplace(tempState);
            if (SaveStates)
                endState = tempState;
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

    if (SaveStates)
        return Path(steps, state, endState);
    else
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
        Path path = Walk(heuristic, bestState, &current);
        if (path.steps.size() > 1) {
            _totalSteps += path.steps.size();
            paths.push_back(path);
            pathLengths.push_back(path.steps.size());
        }
        else
            _totalInvalidPaths++;

        if (OnWalkerStep != nullptr)
            OnWalkerStep(this, current);
        _totalIterations++;
    }
    auto ellapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - startTime).count();
    _totalWalkingTime += ellapsed;
    if (OnWalkerEnd != nullptr)
        OnWalkerEnd(this, ellapsed);
    return paths;
}