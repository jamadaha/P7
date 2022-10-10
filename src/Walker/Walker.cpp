#include "Walker.hpp"

void Walker::Walk() {
    int depth = depthFunc->GetDepth();
    PDDLState state = instance->problem->initState;
    for (int i = 0; i < depth; i++) {
        state = DoAction(state, heuristic->NextChoice(actionGenerator.GenerateActions(&state)));

    }
}

PDDLState Walker::DoAction(PDDLState state, PDDLActionInstance action) {
    for (int i = 0; i < action.action.effects.size(); i++) {
        auto effect = action.action.effects[i];
        bool found = false;
        for (int stateIndex = 0; stateIndex < state.state.size(); stateIndex++) {
            if (effect.predicate.name == state.state[stateIndex].predicate.name) {
                bool isEqual = true;
                // Different argument count = not same
                if (effect.predicate.args.size() != state.state[stateIndex].predicate.args.size())
                    continue;

                for (int arg = 0; arg < effect.predicate.args.size(); arg++) {
                    if (action.arguments[effect.predicate.args[arg].index] != state.state[stateIndex].predicate.args[arg].name) {
                        isEqual = false;;
                        break;
                    }
                }
                if (isEqual) {
                    printf("Index %d\n", stateIndex);
                    if (!effect.state)
                        state.state.erase(state.state.begin() + stateIndex);
                    else
                        state.state[stateIndex].state = effect.state;
                    found = true;
                }
            }
        }
        if (!found) {
            for (int predicate = 0; predicate < effect.predicate.args.size(); predicate++)
                effect.predicate.args[predicate].name = action.arguments[effect.predicate.args[predicate].index];
            state.state.push_back(effect);
        }
    }
    return state;
}
