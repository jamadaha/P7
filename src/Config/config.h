#ifndef CONFIG
#define CONFIG

#include <string>
#include "../Helpers/StringHelper.h"

using namespace std;

template <typename T>
struct ConfigItem {
    ConfigItem(T defaultContent) {
        DefaultContent = defaultContent;
    }

    T Content;
    T DefaultContent;
};

struct Options {
    ConfigItem<string> search = ConfigItem<string>("astar");
    ConfigItem<string> heuristic = ConfigItem<string>("blind");
};

class Config {
public:
    ConfigItem<bool> DebugMode = ConfigItem<bool>(false);
    ConfigItem<string> downwardPath = ConfigItem<string>("fast-downward.py");
    Options downwardOptions;
    ConfigItem<string> validatorPath = ConfigItem<string>("validate");
    ConfigItem<string> domainFile = ConfigItem<string>("gripper_domain.pddl");
    ConfigItem<string> problemFile = ConfigItem<string>("gripper_problem.pddl");

    int parseArgs(Config* config, int argc, char** argv);
private:
    static string GetSearchDesc();
    static string GetEvaluatorDesc();
};

#endif
