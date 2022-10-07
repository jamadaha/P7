#include "config.h"
#include <string>
#include <cstring>
#include <iostream>
#include "../../include/cxxopts.hpp"
using namespace std;

int Config::parseArgs(Config* config, int argc, char** argv){
    cxxopts::Options options("P7","Insert what program does");

    options.add_options()
        ("h,help", "Print usage")
        ("d,domain", "Name of domain file", cxxopts::value<std::string>()->default_value("domain.pddl"))
        ("p,problem", "Name of problem file", cxxopts::value<std::string>()->default_value("problem.pddl"))
        ("f,downwardpath", "fast-downward.py filepath", cxxopts::value<std::string>()->default_value("fast-downward.py"))
        ("c,dovalidate", "Should validate intermediate and output plans")
        ("v,validatorpath", "validator filepath", cxxopts::value<std::string>()->default_value("validate"))
        ("s,search", GetSearchDesc().c_str(), cxxopts::value<std::string>()->default_value("astar"))
        ("e,evaluator", GetEvaluatorDesc().c_str(), cxxopts::value<std::string>()->default_value("blind"))
    ;

    auto result = options.parse(argc, argv);
    if (result.count("help")) {
        cout << options.help() << endl;
        return 1;
    }

    const string domainPath = StringHelper::Trim(result["d"].as<string>());
    const string problemPath = StringHelper::Trim(result["p"].as<string>());
    const string downwardpath = StringHelper::Trim(result["f"].as<string>());
    const string validatorPath = StringHelper::Trim(result["v"].as<string>());
    bool doValidate = false;
    if (result["c"].count() != 0)
        doValidate = true;
    const string searchmethod = result["s"].as<string>();
    const string heuristicmethod = result["e"].as<string>();

    config->path = downwardpath;
    config->validatorPath = validatorPath;
    config->validatePlans = doValidate;
    config->domainFile = domainPath;
    config->problemFile = problemPath;
    config->opt = {.search = searchmethod, .heuristic = heuristicmethod};

    return 0;
}

template<typename ... Args>
std::string string_format( const std::string& format, Args ... args )
{
    int size_s = std::snprintf( nullptr, 0, format.c_str(), args ... ) + 1; // Extra space for '\0'
    if( size_s <= 0 ){ throw std::runtime_error( "Error during formatting." ); }
    auto size = static_cast<size_t>( size_s );
    std::unique_ptr<char[]> buf( new char[ size ] );
    std::snprintf( buf.get(), size, format.c_str(), args ... );
    return std::string( buf.get(), buf.get() + size - 1 ); // We don't want the '\0' inside
}

// Options from here https://www.fast-downward.org/Doc/SearchEngine
string Config::GetSearchDesc() {
    return string_format("%s\n%-12s - %s\n%-12s - %s\n%-12s - %s\n%-12s - %s\n%-12s - %s\n%-12s - %s\n%-12s - %s\n%-12s - %s\n%-12s - %s\n",
    "Search Method",
    "astar", "a* Search",
    "eager", "eager best-first search",
    "eager_greedy", "greedy search (eager)",
    "eager_wastar", "eager weighted A*",
    "ehc", "lazy enforced hill-climbing",
    "iterated", "iterated search",
    "lazy", "lazy best-first search",
    "lazy_greedy", "greedy search (lazy)",
    "lazy_wstar", "(weighted) A* search (lazy)");
}

// Options from here https://www.fast-downward.org/Doc/Evaluator
string Config::GetEvaluatorDesc() {
    return string_format("%s\n%-12s - %s\n%-12s - %s\n%-12s - %s\n%-12s - %s\n%-12s - %s\n%-12s - %s\n%-12s - %s\n%-12s - %s\n%-12s - %s\n%-12s - %s\n%-12s - %s\n%-12s - %s\n",
    "Evaluator Method",
    "add", "additive heuristic",
    "blind", "blind heuristic",
    "cea", "context-enchanced additive heuristic",
    "cegar", "additive CEGAR heuristic",
    "cg", "causal graph heuristic",
    "ff", "FF heuristic",
    "hm", "h^m heuristic",
    "hmax", "Max heuristic",
    "lmcut", "Landmark-cut heuristic",
    "merge_and_shrink", "merge-and-shrink heuristic",
    "operatorcounting", "Operator-counting heuristic",
    "ipdb", "canonical pdb with hillclimbing algo");
}
