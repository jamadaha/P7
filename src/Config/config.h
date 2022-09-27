#ifndef CONFIG
#define CONFIG

#include <string>
#include "../Helpers/StringHelper.h"

using namespace std;

struct Options {
    std::string search;
    std::string heuristic;
};

class Config {
public:
    std::string path;
    string domainFile;
    string problemFile;
    Options opt;

    int parseArgs(Config* config, int argc, char** argv);
private:
    static std::string GetSearchDesc();
    static std::string GetEvaluatorDesc();
};

#endif
