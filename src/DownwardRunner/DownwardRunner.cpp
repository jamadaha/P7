#include "DownwardRunner.h"
#include <iostream>

using namespace std;

void DownwardRunner::runDownward(Config config) {
    string path = config.path;
    string search = config.opt.search;
    string heuristic = config.opt.heuristic;
    string domainFile = config.domainFile;
    string problemFile = config.problemFile;

    string command = path + " " + domainFile + " " + problemFile + " --search \"" + search + "(" + heuristic + "())\"";
    system(command.c_str());
}
