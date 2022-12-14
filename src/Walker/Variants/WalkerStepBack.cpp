#include "WalkerStepBack.hpp"

Path WalkerStepBack::Walk(BaseHeuristic *heuristic, const PDDL::State *state, unsigned int* current) {
    std::vector<PDDL::ActionInstance> steps; 
    steps.reserve(maxStepCount);
    std::unordered_set<PDDL::State> visitedStates; 
    visitedStates.reserve(maxStepCount);

    PDDL::State endState;
    PDDL::State tempState = PDDL::State(state->unaryFacts, state->binaryFacts);
    if (OnTempStateMade != nullptr)
        OnTempStateMade(this->instance, &tempState);

    heuristic->Reset();

    bool doBreak = false;
    for (int i = 0; i < maxStepCount; i++) {
        if (!widthFunc->Iterate(current))
            break;

        std::vector<PDDL::ActionInstance> possibleActions;
        possibleActions = actionGenerator.GenerateActions(&tempState);

        if (possibleActions.size() == 0) break;
        PDDL::ActionInstance *chosenAction = heuristic->NextChoice(&tempState, &possibleActions);
        PDDL::DoActionChanges changes = tempState.DoAction(chosenAction);

        while (visitedStates.contains(tempState)) {
            tempState.UndoAction(&changes);
            for (int i = 0; i < possibleActions.size(); i++) {
                if (possibleActions.at(i) == *chosenAction) {
                    possibleActions.erase(possibleActions.begin() + i);
                    break;
                }
            }
            if (possibleActions.size() == 0) {
                doBreak = true;
                break;
            }

            chosenAction = heuristic->NextChoice(&tempState, &possibleActions);
            changes = tempState.DoAction(chosenAction);
        }
        if (doBreak)
            break;

        visitedStates.emplace(tempState);
        if (SaveStates)
            endState = tempState;
        steps.push_back(*chosenAction);

        if (OnStateWalk != nullptr)
            OnStateWalk(this->instance, &tempState, chosenAction);
    }

    if (SaveStates)
        return Path(steps, *state, endState);
    else
        return Path(steps);
}

std::vector<Path> WalkerStepBack::Walk() {
    std::vector<Path> paths;
    unsigned int current;
    if (OnWalkerStart != nullptr)
        OnWalkerStart(this);
    auto startTime = std::chrono::steady_clock::now();
    while (widthFunc->Iterate(&current)) {
        Path path = Walk(heuristic, &this->instance->problem->initState, &current);
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
