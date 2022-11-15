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
        possibleActions = actionGenerator->GenerateActions(&tempState);

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

    auto initState = (this->instance->problem->initState);
    auto goalState = (this->instance->problem->goalState);

    auto startTime = chrono::steady_clock::now();
    while (widthFunc->Iterate(&current)) {
        auto unaryFacts = GetFactSubset<unordered_set<unsigned int>>(&initState.unaryFacts, &goalState.unaryFacts);
        auto binaryFacts = GetFactSubset<unordered_set<pair<unsigned int, unsigned int>>>(&initState.binaryFacts, &goalState.binaryFacts);
        auto multiFacts = GetFactSubset<unordered_set<MultiFact>>(&initState.multiFacts, &goalState.multiFacts);

        PDDLState probe = PDDLState(unaryFacts, binaryFacts, multiFacts);

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

template <typename T>
unordered_map<unsigned int, T> WalkerProbe::GetFactSubset(unordered_map<unsigned int, T>* initSource, unordered_map<unsigned int, T>* goalSource) {
    unordered_map<unsigned int, T>* targetSource;
    if (rand() % 2)
        targetSource = initSource;
    else
        targetSource = goalSource;

    unordered_map<unsigned int, T> returnSet;
    for (auto i : *targetSource) {
        if (this->instance->domain->staticPredicates.contains(i.first)) {
            returnSet.emplace(i.first, initSource->at(i.first));
        }
        else {
            T newSet;
            for (auto j : i.second) {
                if (rand() % 2)
                    newSet.emplace(j);
            }
            returnSet.emplace(i.first, newSet);
        }
    }
    return returnSet;
}
