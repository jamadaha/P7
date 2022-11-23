#include "Regressor.hh"

Path Regressor::RegressFromState(const PDDLState *state) {
    std::vector<PDDLActionInstance> steps;
    PDDLState tempState = PDDLState(*state);
    for (int i = 0; i < this->depthFunction->GetDepth(); i++) {
        std::vector<PartialAction> partialActions = actionGenerator.ExpandState(&tempState);
        if (partialActions.size() == 0)
            break;
        
        std::vector<RegressionStep> possibleRegressions = GetPredecessorStates(&tempState, &partialActions);
    }
    
    return Path(steps);
}

std::vector<Regressor::RegressionStep> Regressor::GetPredecessorStates(const PDDLState *state, const std::vector<PartialAction> *actions) {
    std::vector<Regressor::RegressionStep> steps;
    for (int i = 0; i < actions->size(); i++)
        AlgorithmHelper::InsertAll(steps, GetPredecessorStates(state, &actions->at(i)));
    return steps;
}

std::vector<Regressor::RegressionStep> Regressor::GetPredecessorStates(const PDDLState *state, const PartialAction *action) {
    std::vector<Regressor::RegressionStep> resultSteps;
    std::vector<PDDLActionInstance> actions = actionConverter.ConvertAction(state, action);
    for (int i = 0; i < actions.size(); i++) {
        PDDLState resultState = GetPredecessorState(state, &actions.at(i));
        if (IsLegal(&resultState))
            resultSteps.push_back(Regressor::RegressionStep(resultState, actions.at(i)));
    }
    return resultSteps;
}

PDDLState Regressor::GetPredecessorState(const PDDLState *state, const PDDLActionInstance *action) {

}

bool Regressor::IsLegal(const PDDLState *state) {
    return true;
}