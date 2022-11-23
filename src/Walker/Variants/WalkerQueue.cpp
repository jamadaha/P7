#include "WalkerQueue.hpp"

Path WalkerQueue::Walk(BaseHeuristic *heuristic, const PDDLState state) {
    auto currentNode = searchQueue.begin();
    auto currentState = PDDLState((*currentNode).second.first);
    auto currentPath = Path((*currentNode).second.second);


    auto actions = actionGenerator.GenerateActions(&currentState);
    for (auto iter = actions.begin(); iter != actions.end(); iter++) {
        currentPath.steps.push_back((*iter));
        auto changes = currentState.DoAction(&(*iter));
        auto eval = heuristic->Eval(&currentState);
        searchQueue.emplace(std::make_pair(eval, std::make_pair(currentState, currentPath)));
        currentState.UndoAction(&changes);
        currentPath.steps.pop_back();
    }

    searchQueue.erase(currentNode);
    if (SaveStates)
        return Path(currentPath.steps, state, currentState);
    else
        return currentPath;
}

std::vector<Path> WalkerQueue::Walk() {
    std::vector<Path> paths;
    unsigned int current;
    if (OnWalkerStart != nullptr)
        OnWalkerStart(this);

    searchQueue.emplace(std::make_pair(0, std::make_pair(this->instance->problem->initState, Path(std::vector<PDDLActionInstance>()))));

    auto startTime = std::chrono::steady_clock::now();
    while (widthFunc->Iterate(&current)) {
        if (searchQueue.size() == 0)
            break;
        Path path = Walk(heuristic, this->instance->problem->initState);
        if (path.steps.size() > 1)
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
