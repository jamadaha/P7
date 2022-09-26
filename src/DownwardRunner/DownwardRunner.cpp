#include "DownwardRunner.h"
#include <iostream>

// assumes domain and problem are called domain.pddl and problem.pddl
void DownwardRunner::runDownward(Config c) {
    string search = Config::stringifySearch(c.opt);
    string heuristic = Config::stringifyHeuristic(c.opt);

    string command = c.path + " domain.pddl problem.pddl --search \"" + search + "(" + heuristic + "())\"";
    //cout << command;
    system(command.c_str());
}