#include "WalkerQueue.hpp"

std::unordered_set<Path> WalkerQueue::Walk(BaseHeuristic *heuristic, const PDDLState *state) {
    auto currentNode = searchQueue.begin();
    auto currentState = PDDLState((*currentNode).second.first);
    auto currentPath = Path((*currentNode).second.second);

    auto paths = std::unordered_set<Path>();

    auto actions = actionGenerator.GenerateActions(&currentState);
    for (auto iter = actions.begin(); iter != actions.end(); iter++) {
        currentPath.steps.push_back((*iter));
        currentState.DoAction(&(*iter));
        auto eval = heuristic->Eval(&currentState);
        searchQueue.emplace(std::make_pair(eval, std::make_pair(currentState, currentPath)));
        paths.emplace(currentPath);
        currentState.UndoAction(&(*iter));
        currentPath.steps.pop_back();
    }

    searchQueue.erase(currentNode);
    return paths;
}

std::vector<Path> WalkerQueue::Walk() {
    std::vector<Path> paths;
    unsigned int current;
    if (OnWalkerStart != nullptr)
        OnWalkerStart(this);

    searchQueue.emplace(std::make_pair(0, std::make_pair(this->instance->problem->initState, Path(std::vector<PDDLActionInstance>()))));

    auto startTime = std::chrono::steady_clock::now();
    while (widthFunc->Iterate(&current)) {
        auto tempPaths = Walk(heuristic, &this->instance->problem->initState);
        for (auto iter = tempPaths.begin(); iter != tempPaths.end(); iter++)
            paths.push_back(*iter);

        if (OnWalkerStep != nullptr)
            OnWalkerStep(this, current);
        _totalIterations++;
    }
    auto ellapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - startTime).count();
    if (OnWalkerEnd != nullptr)
        OnWalkerEnd(this, ellapsed);
    return paths;
}
