#ifndef SAS_PARSER
#define SAS_PARSER

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <filesystem>

using namespace std;

struct SASAction {
public:
    std::string name;
    std::vector<std::string> parameters;

    SASAction(std::string name, std::vector<std::string> parameters) : name(name), parameters(parameters) {}
};

struct SASPlan {
public:
    std::vector<SASAction> actions;
    int cost;

    SASPlan(std::vector<SASAction> actions, int cost) : actions(actions), cost(cost) {}
};

class SASParser {
public:
    SASPlan Parse(std::filesystem::path path);
    SASPlan Parse(std::string SAS);

private:
    SASAction ParseAction(std::string line);
    int ParseCost(std::string line);
};

#endif
