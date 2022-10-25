#include "Walker.hpp"

Path Walker::Walk(Config* config) {
    return Walk(config, instance->problem->initState);
}

Path Walker::Walk(Config* config, PDDLState state) {
    int depth = depthFunc->GetDepth();
    std::vector<PDDLActionInstance> steps;
    steps.reserve(depth);
    PDDLState *tempState = new PDDLState(state.unaryFacts, state.multiFacts);
    for (int i = 0; i < depth; i++) {
        std::vector<PDDLActionInstance> actions = actionGenerator.GenerateActions(tempState);
        if (actions.size() == 0)
            break;
        PDDLActionInstance action = heuristic->NextChoice(actions);
        totalActions += actions.size();
        steps.push_back(action);

        DoAction(tempState, &action);

        if (config->GetBool("printwalkersteps")) {
            std::cout << tempState->ToString(this->instance);

            std::cout << action.ToString(this->instance);
        }
        
        
    }
    free(tempState);
    return Path(steps);
}

void Walker::DoAction(PDDLState *state, const PDDLActionInstance *action) {
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
            if (effect.value) {
                if (state->ContainsFact(effect.predicateIndex, &effect.args, &action->objects))
                    continue;
                
                state->multiFacts.at(effect.predicateIndex).push_back(MultiFact(&effect.args, &action->objects));
            } else {
                if (!state->ContainsFact(effect.predicateIndex, &effect.args, &action->objects))
                    continue;
                auto factSet = &state->multiFacts.at(effect.predicateIndex);
                factSet->erase(std::remove(factSet->begin(), factSet->end(), std::make_pair(&effect.args, &action->objects)), factSet->end());
            }
        }
    }
}
