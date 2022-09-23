#ifndef SAS_PARSER
#define SAS_PARSER

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

struct Action {
public:
    std::string name;
    std::vector<std::string> parameters;

    Action(std::string name, std::vector<std::string> parameters) : name(name), parameters(parameters) {}
};

struct Plan {
public:
    std::vector<Action> actions;
    int cost;

    Plan(std::vector<Action> actions, int cost) : actions(actions), cost(cost) {}
};

class SAS_Parser {
public:
    Plan Parse(std::string path);

private:
    Action ParseAction(std::string line);
    int ParseCost(std::string line);
};

#endif
