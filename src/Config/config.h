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
    ConfigItem<string> Search = ConfigItem<string>("astar");
    ConfigItem<string> Heuristic = ConfigItem<string>("blind");
};

class Config {
public:
    ConfigItem<bool> DebugMode = ConfigItem<bool>(false);
    ConfigItem<string> DownwardPath = ConfigItem<string>("fast-downward.py");
    Options DownwardOptions;
    ConfigItem<string> ValidatorPath = ConfigItem<string>("validate");
    ConfigItem<string> DomainFile = ConfigItem<string>("gripper_domain.pddl");
    ConfigItem<string> ProblemFile = ConfigItem<string>("gripper_problem.pddl");

    int ParseArgs(Config* config, int argc, char** argv);
private:
    static string GetSearchDesc();
    static string GetEvaluatorDesc();
};

#endif
