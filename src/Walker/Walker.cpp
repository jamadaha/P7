#include "Walker.hpp"


Path Walker::Walk(BaseHeuristic *heuristic, BaseDepthFunction *depthFunc, const PDDLState *state) {
    const int depth = depthFunc->GetDepth();
    std::vector<PDDLActionInstance> steps; steps.reserve(depth);
    std::unordered_set<PDDLState> visitedStates; visitedStates.reserve(depth);

    PDDLState tempState = PDDLState(state->unaryFacts, state->multiFacts);
   
    if (OnTempStateMade != nullptr)
        OnTempStateMade(this->instance, &tempState);

    for (int i = 0; i < depth; i++) {
        std::vector<PDDLActionInstance> possibleActions;
        //report->Resume(reportActionGenID);
        possibleActions = actionGenerator.GenerateActions(&tempState);
        //report->Pause(reportActionGenID);

        if (possibleActions.size() == 0) break;
        //report->Resume(reportHeuristicID);
        PDDLActionInstance *chosenAction = heuristic->NextChoice(&tempState, &possibleActions);
        //report->Pause(reportHeuristicID);
        tempState.DoAction(chosenAction);

        if (visitedStates.contains(tempState))
            break;
        else {
            visitedStates.emplace(tempState);
            steps.push_back(*chosenAction);

            if (OnStateWalk != nullptr)
                OnStateWalk(this->instance, &tempState, chosenAction);
        }
    }

    return Path(steps);
}

std::vector<Path> Walker::Walk(BaseHeuristic *heuristic, BaseDepthFunction *depthFunc, BaseWidthFunction *widthFunc) {
    ProgressBarHelper* bar;

    //reportActionGenID = report->Begin("Action Generation"); report->Pause(reportActionGenID);
    //reportHeuristicID = report->Begin("Heuristic"); report->Pause(reportHeuristicID);

    std::vector<Path> paths;
    unsigned int current;
    if (OnWalkerStart != nullptr)
        OnWalkerStart();
    while (widthFunc->Iterate(&current)) {
        Path path = Walk(heuristic, depthFunc, &this->instance->problem->initState);
        paths.push_back(path);

        if (OnWalkerStep != nullptr)
            OnWalkerStep(current);
    }
    if (OnWalkerEnd != nullptr)
        OnWalkerEnd();
    //report->Stop(reportActionGenID); report->Stop(reportHeuristicID);
    return paths;
}