#include "BaseRegressor.hh"

#include <chrono>

std::vector<Path> BaseRegressor::Regress() {
    std::vector<Path> paths;
    unsigned int current = 0;
    auto startTime = std::chrono::steady_clock::now();
    while (widthFunction->Iterate(&current))
        paths.push_back(RegressFromState(&this->instance->problem->goalState, &current));

    auto ellapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - startTime).count();
    return paths;
}

void BaseRegressor::GetPredecessorState(PDDL::State *state, const PDDL::ActionInstance *action) {
    // Handle effects
    // Assumes that positive effects were untrue before action
    for (int i = 0; i < action->action->effects.size(); i++) {
        auto effect = &action->action->effects.at(i);
        if (effect->args.size() == 1) {
            if (effect->value)
                state->unaryFacts.at(effect->predicateIndex).erase(action->objects.at(effect->args.at(0)));
            else
                state->unaryFacts.at(effect->predicateIndex).emplace(action->objects.at(effect->args.at(0)));
        } else {
            if (effect->value)
                state->binaryFacts.at(effect->predicateIndex).erase(std::make_pair(action->objects.at(effect->args.at(0)), action->objects.at(effect->args.at(1))));
            else
                state->binaryFacts.at(effect->predicateIndex).emplace(std::make_pair(action->objects.at(effect->args.at(0)), action->objects.at(effect->args.at(1))));
        }
    }

    // Handle preconditions
    for (int i = 0; i < action->action->preconditions.size(); i++) {
        auto precondition = &action->action->preconditions.at(i);
        if (precondition->args.size() == 1) {
            if (precondition->value)
                state->unaryFacts.at(precondition->predicateIndex).emplace(action->objects.at(precondition->args.at(0)));
            else
                state->unaryFacts.at(precondition->predicateIndex).erase(action->objects.at(precondition->args.at(0)));
        } else {
            if (precondition->value)
                state->binaryFacts.at(precondition->predicateIndex).emplace(std::make_pair(action->objects.at(precondition->args.at(0)), action->objects.at(precondition->args.at(1))));
            else
                state->binaryFacts.at(precondition->predicateIndex).erase(std::make_pair(action->objects.at(precondition->args.at(0)), action->objects.at(precondition->args.at(1))));
        }
    }
}
