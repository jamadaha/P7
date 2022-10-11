#include "Walker.hpp"

void Walker::Walk() {
    int depth = depthFunc->GetDepth();
    PDDLState state = instance->problem->initState;
    for (int i = 0; i < depth; i++) {
        auto actions = actionGenerator.GenerateActions(&state);
        if (actions.size() == 0)
            return;
        state = DoAction(state, heuristic->NextChoice(actions));

    }
}

PDDLState Walker::DoAction(PDDLState state, PDDLActionInstance action) {
    // For each action effect, change the state accordingly
    for (int i = 0; i < action.action.effects.size(); i++) {
        auto effect = action.action.effects[i];
        state.Update(effect);
    }
    
    return state;
}
