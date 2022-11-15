#ifndef SAS_PARSER_HH
#define SAS_PARSER_HH

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <filesystem>

#include "../Helpers/StringHelper.hh"

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
    int macrosUsed;

    SASPlan(std::vector<SASAction> actions, int cost, int macrosUsed) : actions(actions), cost(cost), macrosUsed(macrosUsed) {}
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
