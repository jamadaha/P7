#include "BaseRegressor.hh"

#include <chrono>

std::vector<Path> BaseRegressor::Regress() {
    std::vector<Path> paths;
    unsigned int current;
    auto startTime = std::chrono::steady_clock::now();
    while (widthFunction->Iterate(&current))
        paths.push_back(RegressFromState(&this->instance->problem->goalState));

    auto ellapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - startTime).count();
    return paths;
}
