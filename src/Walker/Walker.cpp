#include "Walker.hpp"

Path Walker::Walk() {
    return Walk(instance->problem->initState);
}

Path Walker::Walk(PDDLState state) {
    int depth = depthFunc->GetDepth();
    std::vector<PDDLActionInstance> steps;
    steps.reserve(depth);
    PDDLState *tempState = new PDDLState(state.unaryFacts, state.multiFacts);
    for (int i = 0; i < depth; i++) {
        auto actions = actionGenerator.GenerateActions(tempState);
        auto action = heuristic->NextChoice(actions);
        steps.push_back(action);
        tempState = DoAction(tempState, &action);
    }
    free(tempState);    
    return Path(steps);
}

PDDLState* Walker::DoAction(PDDLState *state, const PDDLActionInstance *action) {
    PDDLState *newState = state->Do(action);
    free(state);
    return newState;
}
