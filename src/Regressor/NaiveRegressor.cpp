#include "NaiveRegressor.hh"

#include <queue>

std::vector<Path> NaiveRegressor::Regress(const PDDLState *state) {
    // For given state, find all actions that has effects related to the facts
        // I.e. gripper ball-at ball1 roomb, where the only action that has that predicate in positive effects is drop
    // Find all variants of the given action that needed
        // I.e. state = ((ball-at ball1 roomb) (ball-at ball2 roomb) (ball-at ball3 rooma))
        // Makes two actions ((drop ball1 roomb) (drop ball2...)
    //
    printf("Lol\n");
}