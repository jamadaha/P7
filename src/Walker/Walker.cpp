#include "Walker.hpp"

Path Walker::Walk() {
    return Walk(instance->problem->initState);
}

Path Walker::Walk(PDDLState state) {
    int depth = depthFunc->GetDepth();
    std::vector<PDDLActionInstance*> steps;
    steps.reserve(depth);
    PDDLState *tempState = new PDDLState(state.unaryFacts, state.multiFacts);
    for (int i = 0; i < depth; i++) {
        std::vector<PDDLActionInstance*> actions = actionGenerator.GenerateActions(tempState);
        if (actions.size() == 0)
            break;
        PDDLActionInstance* action = heuristic->NextChoice(actions);
        totalActions += actions.size();
        steps.push_back(action);
        tempState = DoAction(tempState, &action);

        std::cout << action.ToString(this->instance->problem, this->instance->domain);
    }
    free(tempState);
    return Path(steps);
}

PDDLState* Walker::DoAction(PDDLState *state, const PDDLActionInstance *action) {
    int actionEffectLength = action->action->effects.size();
    for (int i = 0; i < actionEffectLength; i++) {
        PDDLLiteral effect = action->action->effects.at(i);
        if (effect.args.size() == 1) {
            // Handle unary effect
            if (effect.value)
                state->unaryFacts.at(effect.predicateIndex).emplace(action->objects.at(effect.args.at(0)));
            else
                state->unaryFacts.at(effect.predicateIndex).erase(action->objects.at(effect.args.at(0)));
        } else {
            // Handle multi effect
            int index = -1;
            int multiFactLength = state->multiFacts.at(effect.predicateIndex).size();
            for (int f = 0; f < multiFactLength; f++) {
                bool equal = true;
                int argLength = effect.args.size();
                for (int e = 0; e < argLength; e++) {
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
                    int argLength = effect.args.size();
                    for (int i = 0; i < argLength; i++)
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
