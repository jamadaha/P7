#include "config.h"
#include <string>
#include <cstring>
#include <iostream>
using namespace std;

int main(){
    Options o = {.search = Astar, .heuristic = Blind};
    Config c = Config("~/downward-projects/downward/fast-downward.py", o);

    string search;
    string heuristic;

    switch(c.opt.search) {
        case Astar:
            search = "astar";
            break;
        case Eager:
            search = "eager";
            break;
        case EagerGreedy:
            search = "eager_greedy";
            break;
        case EagerWAstar:
            search = "eager_wastar";
            break;
        case Ehc:
            search = "ehc";
            break;
        case Iterated:
            search = "iterated";
            break;
        case Lazy:
            search = "lazy";
            break;
        case LazyGreedy:
            search = "lazy_greedy";
            break;
        case LazyWAstar:
            search = "lazy_wstar";
            break;
    }

    switch(c.opt.heuristic) {
        case Add:
            heuristic = "add";
            break;
        case Blind:
            heuristic = "blind";
            break;
        case Cea:
            heuristic = "cea";
            break;
        case Cegar:
            heuristic = "cegar";
            break;
        case Cg:
            heuristic = "cg";
            break;
        case Ff:
            heuristic = "ff";
            break;
        case Hm:
            heuristic = "hm";
            break;
        case Hmax:
            heuristic = "hmax";
            break;
        case Lmcut:
            heuristic = "lmcut";
            break;
        case MergeAndShrink:
            heuristic = "merge_and_shrink";
            break;
        case OperatorCounting:
            heuristic = "operatorcounting";
            break;
        case Ipdb:
            heuristic = "ipdb";
            break;
    }

    string command = c.path + " domain.pddl problem.pddl --search \"" + search + "(" + heuristic + "())\"";
    cout << command;
    //string command = c1 + c.path + " --help";
    system(command.c_str());
}