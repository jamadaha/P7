#include "DownwardRunner.h"
#include <iostream>

using namespace std;

void DownwardRunner::runDownward(Config config, string reformulatedDomain, string reformulatedProblem) {
    string path = config.path;
    string search = config.opt.search;
    string heuristic = config.opt.heuristic;

    string command = path + " " + reformulatedDomain + " " + reformulatedProblem + " --search \"" + search + "(" + heuristic + "())\"";
    system(command.c_str());
}
