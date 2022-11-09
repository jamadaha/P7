#include "WalkerProbe.hpp"

using namespace std;

Path WalkerProbe::Walk(BaseHeuristic* heuristic, const PDDLState* state) {
    vector<PDDLActionInstance> steps; steps.reserve(maxStepCount);
    unordered_set<PDDLState> visitedStates; visitedStates.reserve(maxStepCount);

    PDDLState tempState = PDDLState(state->unaryFacts, state->binaryFacts, state->multiFacts);
    if (OnTempStateMade != nullptr)
        OnTempStateMade(this->instance, &tempState);

    for (int i = 0; i < maxStepCount; i++) {
        vector<PDDLActionInstance> possibleActions;
        possibleActions = actionGenerator.GenerateActions(&tempState);

        if (possibleActions.size() == 0) break;
        PDDLActionInstance* chosenAction = heuristic->NextChoice(&tempState, &possibleActions);
        tempState.DoAction(chosenAction);

        if (visitedStates.contains(tempState))
            break;
        else {
            visitedStates.emplace(tempState);
            steps.push_back(*chosenAction);

            if (OnStateWalk != nullptr)
                OnStateWalk(this->instance, &tempState, chosenAction);
        }
    }

    return Path(steps);
}

vector<Path> WalkerProbe::Walk() {
    vector<Path> paths;
    unsigned int current;
    if (OnWalkerStart != nullptr)
        OnWalkerStart(this);

    srand(time(NULL));
    bool takeInitState = true;

    auto startTime = chrono::steady_clock::now();
    while (widthFunc->Iterate(&current)) {
        auto unarySource = &(this->instance->problem->initState).unaryFacts;
        unordered_map<unsigned int, unordered_set<unsigned int>> unaryFacts;
        if (!takeInitState) {
            unarySource = &(this->instance->problem->goalState).unaryFacts;
        }
        for (auto i : *unarySource) {
            unordered_set<unsigned int> newSet;
            for (auto j : i.second) {
                if (rand() & 2)
                    newSet.emplace(j);
            }
            unaryFacts.emplace(i.first, newSet);
        }

        auto binarySource = &(this->instance->problem->initState).binaryFacts;
        unordered_map<unsigned int, unordered_set<pair<unsigned int, unsigned int>>> binaryFacts;
        if (!takeInitState) {
            binarySource = &(this->instance->problem->goalState).binaryFacts;
        }
        for (auto i : *binarySource) {
            unordered_set<pair<unsigned int, unsigned int>> newSet;
            for (auto j : i.second) {
                if (rand() & 2)
                    newSet.emplace(j);
            }
            binaryFacts.emplace(i.first, newSet);
        }

        auto multiSource = &(this->instance->problem->initState).multiFacts;
        unordered_map<unsigned int, unordered_set<MultiFact>> multiFacts;
        if (!takeInitState) {
            multiSource = &(this->instance->problem->goalState).multiFacts;
        }
        for (auto i : *multiSource) {
            unordered_set<MultiFact> newSet;
            for (auto j : i.second) {
                if (rand() & 2)
                    newSet.emplace(j);
            }
            multiFacts.emplace(i.first, newSet);
        }

        takeInitState = !takeInitState;

        PDDLState probe = PDDLState(this->instance->problem->initState.unaryFacts, binaryFacts, multiFacts);

        Path path = Walk(heuristic, &probe);
        paths.push_back(path);

        if (OnWalkerStep != nullptr)
            OnWalkerStep(this, current);
        _totalIterations++;
    }
    auto ellapsed = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - startTime).count();
    if (OnWalkerEnd != nullptr)
        OnWalkerEnd(this, ellapsed);
    return paths;
}
