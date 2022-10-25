#include "Walker.hpp"


Path Walker::Walk(BaseHeuristic *heuristic, BaseDepthFunction *depthFunc, const PDDLState *state) {
    const int depth = depthFunc->GetDepth();
    std::vector<PDDLActionInstance> steps; steps.reserve(depth);
    std::unordered_set<PDDLState> visitedStates; visitedStates.reserve(depth);

    PDDLState tempState = PDDLState(state->unaryFacts, state->multiFacts);
    for (int i = 0; i < depth; i++) {
        std::vector<PDDLActionInstance> possibleActions = actionGenerator.GenerateActions(&tempState);
        if (possibleActions.size() == 0) break;
        PDDLActionInstance *chosenAction = heuristic->NextChoice(&tempState, &possibleActions);
        tempState.DoAction(chosenAction);

        if (visitedStates.contains(tempState))
            break;
        else {
            visitedStates.emplace(tempState);
            steps.push_back(*chosenAction);
        }
    }

    return Path(steps);
}

