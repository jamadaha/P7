#include "Walker.hpp"

Path Walker::Walk(Config* config) {
    return Walk(config, instance->problem->initState);
}

Path Walker::Walk(Config* config, PDDLState state) {
    int depth = depthFunc->GetDepth();
    std::unordered_set<PDDLState> visitedStates;
    visitedStates.reserve(depth);
    std::vector<PDDLActionInstance> steps;
    steps.reserve(depth);
    PDDLState *tempState = new PDDLState(state.unaryFacts, state.multiFacts);
    for (int i = 0; i < depth; i++) {
        
        std::vector<PDDLActionInstance> actions = actionGenerator.GenerateActions(tempState);
        if (actions.size() == 0)
            break;
        PDDLActionInstance *action = heuristic->NextChoice(&actions);
        totalActions += actions.size();
        
        tempState->DoAction(action);

        if (visitedStates.contains(*tempState))
            break;
        else {
            visitedStates.emplace(*tempState);
            steps.push_back(*action);
        }

        if (config->GetBool("printwalkersteps")) {
            std::cout << tempState->ToString(this->instance);

            std::cout << action->ToString(this->instance);
        }
    }
    free(tempState);
    return Path(steps);
}
