#include "Walker.hpp"

void Walker::Walk() {
    int depth = depthFunc->GetDepth();
    PDDLState state = instance->problem->initState;
    for (int i = 0; i < depth; i++) {
        std::vector<PDDLActionInstance> actions = actionGenerator.GenerateActions(&state);
    }
}
