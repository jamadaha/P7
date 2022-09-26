#include "config.h"
#include <string>
#include <cstring>
#include <iostream>
using namespace std;

// assumes domain and problem pddls are called "domain.pddl" and "problem.pddl"
int main(){
    Options o = {.search = Astar, .heuristic = Blind};
    Config c = Config("~/downward-projects/downward/fast-downward.py", o);

    string search = c.stringifySearch();
    string heuristic = c.stringifyHeuristic();

    string command = c.path + " domain.pddl problem.pddl --search \"" + search + "(" + heuristic + "())\"";
    cout << command;
    //string command = c1 + c.path + " --help";
    //system(command.c_str());
}