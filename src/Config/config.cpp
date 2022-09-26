#include "config.h"
#include <string>
#include <cstring>
#include <iostream>
#include "../../include/cxxopts.hpp"
using namespace std;

Config Config::parseArgs(int argc, char** argv){
    // create options
    cxxopts::Options options("test","interesting description");

    options.add_options()
        ("d,downwardpath", "fast-downward.py filepath", cxxopts::value<std::string>()->default_value("fast-downward.py")) 
        ("s,search", "Search method", cxxopts::value<std::string>()->default_value("astar"))
        ("h,heuristic", "Evaluator method", cxxopts::value<std::string>()->default_value("blind"))
    ;

    auto result = options.parse(argc, argv);
    string downwardpath = result["d"].as<string>();
    string searchmethod = result["s"].as<string>();
    string heuristicmethod = result["h"].as<string>();

    Options o = {.search = Config::enumerateSearch(searchmethod), .heuristic = Config::enumerateHeuristic(heuristicmethod)};
    Config c = Config(downwardpath, o);

    return c;
}

Search Config::enumerateSearch(string search) {
    if (search == "astar")
        return Astar;
    else if (search == "eager")
        return Eager;
    else if (search == "eager_greedy")
        return EagerGreedy;
    else if (search == "eager_wastar")
        return EagerWAstar;
    else if (search == "ehc")
        return Ehc;
    else if (search == "iterated")
        return Iterated;
    else if (search == "lazy")
        return Lazy;
    else if (search == "lazy_greedy")
        return LazyGreedy;
    else if (search == "lazy_wstar")
        return LazyWAstar;
    else
        return Iterated;
}

Heuristic Config::enumerateHeuristic(string heuristic) {
    if (heuristic == "add")
        return Add;
    else if (heuristic == "blind")
        return Blind;
    else if (heuristic == "cea")
        return Cea;
    else if (heuristic == "cegar")
        return Cegar;
    else if (heuristic == "cg")
        return Cg;
    else if (heuristic == "ff")
        return Ff;
    else if (heuristic == "hm")
        return Hm;
    else if (heuristic == "hmax")
        return Hmax;
    else if (heuristic == "lmcut")
        return Lmcut;
    else if (heuristic == "merge_and_shrink")
        return MergeAndShrink;
    else if (heuristic == "operatorcounting")
        return OperatorCounting;
    else if (heuristic == "ipdb")
        return Ipdb;
    else
        return Blind;
}

string Config::stringifySearch(Options opt) {
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

string Config::stringifyHeuristic(Options opt) {
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