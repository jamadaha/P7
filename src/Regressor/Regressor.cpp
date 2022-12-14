#include "Regressor.hh"

Path Regressor::RegressFromState(const PDDL::State *state, unsigned int* current) {
    std::vector<PDDL::ActionInstance> steps;
    std::unordered_set<PDDL::State> visitedStates{*state};
    PDDL::State tempState = PDDL::State(*state);
    for (int i = 0; i < this->depthFunction->GetDepth(); i++) {
        if (!widthFunction->Iterate(current))
            break;

        std::vector<PartialAction> partialActions = actionGenerator.ExpandState(&tempState);
        if (partialActions.size() == 0)
            break;
        if (!widthFunction->Iterate(current))
            break;
        
        bool foundLegalPredecessor;
        auto priorState = tempState;
        auto action = GetLegalPredecessor(&partialActions, &tempState, &foundLegalPredecessor);

        if (!foundLegalPredecessor || visitedStates.contains(tempState)) {
            tempState = priorState;
            break;
        } else {
            visitedStates.emplace(tempState);
            steps.push_back(action);
        }
    }

    auto reversedSteps = AlgorithmHelper::Reverse(steps);
    return Path(reversedSteps, tempState, *state);
}

PDDL::ActionInstance Regressor::GetLegalPredecessor(const std::vector<PartialAction> *actions, PDDL::State *state, bool *sucess) {
    const unsigned int init = rand() % actions->size();
    for (unsigned int i = 0; i < actions->size(); i++) {
        const unsigned int current = (init + i) % actions->size();
        const PartialAction *partialAction = &actions->at(current);
        auto candidateActions = actionConverter.ConvertAction(state, partialAction);
        for (int t = 0; t < candidateActions.size(); t++) {
            auto action = &candidateActions.at(t);
            auto tempState = *state;
            GetPredecessorState(&tempState, action);
            (*sucess) = true;
            (*state) = tempState;
            return *action;
        }
    }
    (*sucess) = false;
    return PDDL::ActionInstance();
}
