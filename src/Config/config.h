#ifndef CONFIG
#define CONFIG

#include <string>

struct Options {
    std::string search;
    std::string heuristic;
};

class Config {
public:
    std::string path;
    Options opt;

    int parseArgs(Config* config, int argc, char** argv);
private:
    static std::string GetSearchDesc();
    static std::string GetEvaluatorDesc();
};

#endif
