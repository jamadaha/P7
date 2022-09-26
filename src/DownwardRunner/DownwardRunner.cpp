#include "DownwardRunner.h"
#include <iostream>

using namespace std;

// assumes domain and problem are called domain.pddl and problem.pddl
void DownwardRunner::runDownward(Config config) {
    string path = config.path;
    string search = config.opt.search;
    string heuristic = config.opt.heuristic;

    string command = path + " domain.pddl problem.pddl --search \"" + search + "(" + heuristic + "())\"";
    system(command.c_str());
}
