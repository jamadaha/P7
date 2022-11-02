#include "Walker.hpp"


Path Walker::Walk(BaseHeuristic *heuristic, BaseDepthFunction *depthFunc, const PDDLState *state) {
    const int depth = depthFunc->GetDepth();
    std::vector<PDDLActionInstance> steps; steps.reserve(depth);
    std::unordered_set<PDDLState> visitedStates; visitedStates.reserve(depth);

    PDDLState tempState = PDDLState(state->unaryFacts, state->multiFacts);
   
    if (OnTempStateMade != nullptr)
        OnTempStateMade(this->instance, &tempState);

    for (int i = 0; i < depth; i++) {
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

            if (OnStateWalk != nullptr)
                OnStateWalk(this->instance, &tempState, chosenAction);
        }
    }

    return Path(steps);
}

std::vector<Path> Walker::Walk(BaseHeuristic *heuristic, BaseDepthFunction *depthFunc, BaseWidthFunction *widthFunc) {
    ProgressBarHelper* bar;

    std::vector<Path> paths;
    unsigned int current;
    if (OnWalkerStart != nullptr)
        OnWalkerStart();
    while (widthFunc->Iterate(&current)) {
        Path path = Walk(heuristic, depthFunc, &this->instance->problem->initState);
        paths.push_back(path);

        if (OnWalkerStep != nullptr)
            OnWalkerStep(current);
    }
    if (OnWalkerEnd != nullptr)
        OnWalkerEnd();
    return paths;
}