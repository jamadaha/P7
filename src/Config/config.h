#ifndef CONFIG_h
#define CONFIG_h

#include <string>
#include "../../include/cxxopts.hpp"
#include "../Helpers/StringHelper.h"

using namespace std;

template <typename T>
struct ConfigItem {
    ConfigItem(char flag, string longFlag, string name, string description, T defaultContent) {
        Flag = flag;
        LongFlag = longFlag;
        Name = name;
        Description = description;
        DefaultContent = defaultContent;
    }

    string Name;
    string Description;
    char Flag;
    string LongFlag;
    T Content;
    T DefaultContent;
};

struct Options {
    ConfigItem<string> Search = ConfigItem<string>('s', "search", "Fast Downward Search", "", "astar");
    ConfigItem<string> Heuristic = ConfigItem<string>('e', "evaluator", "Fast Downward Heuristic", "", "blind");
};

class Config {
public:
    ConfigItem<bool> DebugMode = ConfigItem<bool>('c', "debugmode", "Debug Mode", "Enable additional debugging info and checks", false);
    ConfigItem<string> DownwardPath = ConfigItem<string>('f', "downwardpath", "Fast-Downward Path", "fast-downward.py filepath", "fast-downward.py");
    Options DownwardOptions;
    ConfigItem<string> ValidatorPath = ConfigItem<string>('v', "validatorpath", "VAL validator Path", "validator filepath", "validate");
    ConfigItem<string> DomainFile = ConfigItem<string>('d', "domain", "Domain File", "Path to domain file", "gripper_domain.pddl");
    ConfigItem<string> ProblemFile = ConfigItem<string>('p', "problem", "Problem File", "Path to problem file", "gripper_problem.pddl");

    int ParseArgs(Config* config, int argc, char** argv);

private:
    string GetSearchDesc();
    string GetEvaluatorDesc();
};

#endif
