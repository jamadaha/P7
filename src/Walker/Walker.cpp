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

        if (config->DebugMode.Content) {
            std::cout << tempState->ToString(this->instance);

            DoAction(tempState, &action);

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
            std::vector<unsigned int> indexes;
            for (auto index : effect.args)
            {
                indexes.push_back(action->objects[index]);
            }
            
            if (effect.value) {
                

                if (state->ContainsFact(effect.predicateIndex, indexes))
                    continue;
                
                state->multiFacts.at(effect.predicateIndex).push_back(MultiFact(indexes));
            } else {
                if (!state->ContainsFact(effect.predicateIndex, indexes))
                    continue;
                auto factSet = &state->multiFacts.at(effect.predicateIndex);
                factSet->erase(std::remove(factSet->begin(), factSet->end(), indexes), factSet->end());
            }
        }
    }
}
