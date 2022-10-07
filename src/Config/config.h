#ifndef CONFIG
#define CONFIG

#include <string>
#include "../Helpers/StringHelper.h"

using namespace std;

struct Options {
    string search;
    string heuristic;
};

class Config {
public:
    string path;
    string validatorPath;
    bool validatePlans;
    string domainFile;
    string problemFile;
    Options opt;

    int parseArgs(Config* config, int argc, char** argv);
private:
    static string GetSearchDesc();
    static string GetEvaluatorDesc();
};

#endif
