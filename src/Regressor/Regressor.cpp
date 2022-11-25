#include "Regressor.hh"

Path Regressor::RegressFromState(const PDDLState *state) {
    std::vector<PDDLActionInstance> steps;
    std::unordered_set<PDDLState> visitedStates{*state};
    PDDLState tempState = PDDLState(*state);
    for (int i = 0; i < this->depthFunction->GetDepth(); i++) {
        std::vector<PartialAction> partialActions = actionGenerator.ExpandState(&tempState);
        if (partialActions.size() == 0)
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

PDDLActionInstance Regressor::GetLegalPredecessor(const std::vector<PartialAction> *actions, PDDLState *state, bool *sucess) {
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
    return PDDLActionInstance();
}
