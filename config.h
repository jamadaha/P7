#ifndef CONFIG
#define CONFIG
#include <string>

enum Search {
    Astar,
    LazyGreedy
};

enum Heuristic {
    Lmcut,
    Ipdb,
    Blind
};

struct Options {
    int search;
    int heuristic;
};

struct Config {
    std::string path;
    Options opt;
    Config (std::string p, Options o) {
        Config::path = p;
        Config::opt = o;
    }
};

#endif