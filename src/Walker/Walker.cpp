#include "Walker.hpp"

Path Walker::Walk() {
    return Walk(instance->problem->initState);
}

Path Walker::Walk(PDDLState state) {
    int depth = depthFunc->GetDepth();
    std::vector<PDDLActionInstance> steps;
    steps.reserve(depth);
    unsigned int actionCount = 0;
    unsigned int stepCount = 0;
    PDDLState *tempState = new PDDLState(state.unaryFacts, state.multiFacts);
    for (int i = 0; i < depth; i++) {
        auto actions = actionGenerator.GenerateActions(tempState);
        actionCount += actions.size();
        auto action = heuristic->NextChoice(actions);
        steps.push_back(action);
        stepCount++;
        tempState = DoAction(tempState, &action);
    }
    free(tempState);    
    return Path(steps, actionCount, stepCount);
}

PDDLState* Walker::DoAction(PDDLState *state, const PDDLActionInstance *action) {
    PDDLState *newState = state->Do(action);
    free(state);
    return newState;
}
