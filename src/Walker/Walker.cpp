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
    for (int i = 0; i < action->action->effects.size(); i++) {
        auto effect = action->action->effects.at(i);
        if (effect.args.size() == 1) {
            // Handle unary effect
            if (effect.value)
                state->unaryFacts.at(effect.predicateIndex).emplace(action->objects.at(effect.args.at(0)));
            else
                state->unaryFacts.at(effect.predicateIndex).erase(action->objects.at(effect.args.at(0)));
        } else {
            // Handle multi effect
            int index = -1;
            for (int f = 0; f < state->multiFacts.at(effect.predicateIndex).size(); f++) {
                bool equal = true;
                for (int e = 0; e < effect.args.size(); e++) {
                    if (state->multiFacts.at(effect.predicateIndex).at(f).fact.at(e) !=
                        action->objects.at(effect.args.at(e))) {
                            equal = false;
                            break;
                        }
                }
                if (equal) {
                    index = f;
                    break;
                }
            }
            if (effect.value) {
                if (index == -1) {
                    std::vector<unsigned int> factArgs;
                    factArgs.reserve(effect.args.size());
                    for (int i = 0; i < effect.args.size(); i++)
                        factArgs.push_back(action->objects.at(effect.args.at(i)));
                    state->multiFacts.at(effect.predicateIndex).push_back(MultiFact(factArgs));
                }
            } else {
                if (index != -1) {
                    auto fact = state->multiFacts.at(effect.predicateIndex);
                    fact.erase(fact.begin());
                }
            }
        }
    }
    return state;
}
