#include "Walker.hpp"

Path Walker::Walk() {
    return Walk(instance->problem->initState);
}

Path Walker::Walk(PDDLState state) {
    int depth = depthFunc->GetDepth();
    std::vector<PDDLActionInstance> steps;
    unsigned int actionCount = 0;
    unsigned int stepCount = 0;
    for (int i = 0; i < depth; i++) {
        auto actions = actionGenerator.GenerateActions(&state);
        actionCount += actions.size();
        // Should this be handled?
        if (actions.size() == 0)
            break;
        auto chosenAction = heuristic->NextChoice(actions);
        stepCount++;
        steps.push_back(chosenAction);
    }
    return Path(steps, actionCount, stepCount);
}
