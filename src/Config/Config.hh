#ifndef CONFIG_HH
#define CONFIG_HH

#include <string>
#include <filesystem>

#include "../../include/cxxopts.hpp"
#include "../Helpers/StringHelper.hh"

template <typename T>
struct ConfigItem {
    ConfigItem(std::string flag, std::string longFlag, std::string name, std::string description, T defaultContent) {
        Flag = flag;
        LongFlag = longFlag;
        Name = name;
        Description = description;
        DefaultContent = defaultContent;
    }

    std::string Name;
    std::string Description;
    std::string Flag;
    std::string LongFlag;
    T Content;
    T DefaultContent;
};

struct Options {
    ConfigItem<std::string> Search = ConfigItem<std::string>("s", "search", "Fast Downward Search", "", "astar");
    ConfigItem<std::string> Heuristic = ConfigItem<std::string>("e", "evaluator", "Fast Downward Heuristic", "", "blind");
};

class Config {
public:
    ConfigItem<bool> DebugMode = ConfigItem<bool>("c", "debugmode", "Debug Mode", "Enable additional debugging info and checks", false);
    ConfigItem<std::string> DownwardPath = ConfigItem<std::string>("f", "downwardpath", "Fast-Downward Path", "fast-downward.py filepath", "../P7Requirements/downward/fast-downward.py");
    Options DownwardOptions;
    ConfigItem<std::string> ValidatorPath = ConfigItem<std::string>("v", "validatorpath", "VAL validator Path", "validator filepath", "../P7Requirements/downward/VAL/validate");
    ConfigItem<std::string> DomainFile = ConfigItem<std::string>("d", "domain", "Domain File", "Path to domain file", "../Data/Classical tracks/Gripper/gripper_domain.pddl");
    ConfigItem<std::string> ProblemFile = ConfigItem<std::string>("p", "problem", "Problem File", "Path to problem file", "../Data/Classical tracks/Gripper/gripper_problem.pddl");
    ConfigItem<std::string> Reformulator = ConfigItem<std::string>("r", "reformulator", "Reformulator Algorithm", "What reformulator algorithm to use", "RandomWalker");
    ConfigItem<int> ReformulatorTime = ConfigItem<int>("t", "timelimit", "Reformulator time limiter", "How much time in ms that the reformulator is allowed to walk in", 500);
    ConfigItem<bool> PrintWalkerSteps = ConfigItem<bool>("w", "printwalkersteps", "Print actions and states", "Print each action and state in walker path", false);

    int ParseArgs(Config* config, int argc, char** argv);

private:
    std::string GetSearchDesc();
    std::string GetEvaluatorDesc();
};

#endif
