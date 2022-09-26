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
    static Search enumerateSearch(string s);
    static Heuristic enumerateHeuristic(string s);
    static string stringifySearch(Options o);
    static string stringifyHeuristic(Options o);
    static Config parseArgs(int argc, char** argv);
};

#endif