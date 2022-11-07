#include "BFS.hpp"

// https://en.wikipedia.org/wiki/Breadth-first_search
Path BFS::Walk(BaseHeuristic *heuristic, const PDDLState *state) {
    const int depth = 100;
    std::pair<std::vector<PDDLActionInstance>, unsigned int> bestPath;
    std::vector<PDDLActionInstance> steps; steps.reserve(depth);
    std::unordered_set<PDDLState> visitedStates; visitedStates.reserve(depth);

    PDDLState tempState = PDDLState(state->unaryFacts, state->binaryFacts, state->multiFacts);
    if (OnTempStateMade != nullptr)
        OnTempStateMade(this->instance, &tempState);


    std::queue<std::pair<std::vector<PDDLActionInstance>, PDDLState>> searchQueue;
    searchQueue.push(std::make_pair(steps, tempState));
    for (int i = 0; i < depth; i++) {
        if (searchQueue.size() == 0)
            break;
        
        std::pair<std::vector<PDDLActionInstance>, PDDLState> currentNode = searchQueue.front();
        searchQueue.pop();

        if (!visitedStates.contains(currentNode.second)) {
            visitedStates.emplace(currentNode.second);
            std::vector<PDDLActionInstance> possibleActions = actionGenerator.GenerateActions(&tempState);
            for (auto action : possibleActions) {
                steps.push_back(action);
                tempState.DoAction(&action);
                searchQueue.push(std::make_pair(steps, tempState));
                unsigned int eval = heuristic->Eval(&tempState);
                if (eval > bestPath.second)
                    bestPath = std::make_pair(steps, eval);
                tempState.UndoAction(&action);
                steps.pop_back();
            }
        }
    }

    return Path(bestPath.first);
}
std::vector<Path> BFS::Walk() {
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