#ifndef CONFIG
#define CONFIG
#include <string>
using namespace std;

// https://www.fast-downward.org/Doc/SearchEngine
enum Search {
    Astar, // A* search
    Eager, // eager best-first search
    EagerGreedy, // greedy search (eager)
    EagerWAstar, // eager weighted A*
    Ehc, // lazy enforced hill-climbing
    Iterated, // iterated search
    Lazy, // lazy best-first search
    LazyGreedy, // greedy search (lazy)
    LazyWAstar, // (weighted) A* search (lazy)
};

// https://www.fast-downward.org/Doc/Evaluator
enum Heuristic {
    Add, // additive heuristic
    Blind, // blind heuristic
    Cea, // context-enchanced additive heuristic
    Cegar, // additive CEGAR heuristic
    Cg, // causal graph heuristic
    Ff, // FF heuristic
    Hm, // h^m heuristic
    Hmax, // Max heuristic
    Lmcut, // Landmark-cut heuristic
    MergeAndShrink, // merge-and-shrink heuristic
    OperatorCounting, // Operator-counting heuristic

    Ipdb, // canonical pdb with hillclimbing algo
};

struct Options {
    int search;
    int heuristic;
};

struct Config {
    string path;
    Options opt;
    Config (string p, Options o) {
        Config::path = p;
        Config::opt = o;
    }
    string stringifySearch() {
        string rstring;
        switch(opt.search) {
            case Astar:
                rstring = "astar";
                break;
            case Eager:
                rstring = "eager";
                break;
            case EagerGreedy:
                rstring = "eager_greedy";
                break;
            case EagerWAstar:
                rstring = "eager_wastar";
                break;
            case Ehc:
                rstring = "ehc";
                break;
            case Iterated:
                rstring = "iterated";
                break;
            case Lazy:
                rstring = "lazy";
                break;
            case LazyGreedy:
                rstring = "lazy_greedy";
                break;
            case LazyWAstar:
                rstring = "lazy_wstar";
                break;
        }
        return rstring;
    }
    string stringifyHeuristic() {
        string rstring;
        switch(opt.heuristic) {
            case Add:
                rstring = "add";
                break;
            case Blind:
                rstring = "blind";
                break;
            case Cea:
                rstring = "cea";
                break;
            case Cegar:
                rstring = "cegar";
                break;
            case Cg:
                rstring = "cg";
                break;
            case Ff:
                rstring = "ff";
                break;
            case Hm:
                rstring = "hm";
                break;
            case Hmax:
                rstring = "hmax";
                break;
            case Lmcut:
                rstring = "lmcut";
                break;
            case MergeAndShrink:
                rstring = "merge_and_shrink";
                break;
            case OperatorCounting:
                rstring = "operatorcounting";
                break;
            case Ipdb:
                rstring = "ipdb";
                break;
        }
        return rstring;
    }
};

#endif