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
        auto action = GetLegalPredecessor(&partialActions, &tempState, &foundLegalPredecessor);

        if (!foundLegalPredecessor || visitedStates.contains(tempState))
            break;
        else {
            visitedStates.emplace(tempState);
            steps.push_back(action);
        }
    }
    
    return Path(steps);
}

PDDLActionInstance Regressor::GetLegalPredecessor(const std::vector<PartialAction> *actions, PDDLState *state, bool *sucess) {
    const unsigned int init = rand() % actions->size();
    for (unsigned int i = 0; i < actions->size(); i++) {
        const unsigned int current = (init + i) % actions->size();
        const PartialAction *partialAction = &actions->at(current);
        auto legalActions = actionConverter.ConvertAction(state, partialAction);
        if (legalActions.size() != 0) {
            auto chosenAction = legalActions.at(rand() % legalActions.size());
            GetPredecessorState(state, &chosenAction);
            (*sucess) = true;
            return chosenAction;
        }
        
    }
    (*sucess) = false;
    return PDDLActionInstance();
}
