#include "SASParser.h"
#include "../Helpers/StringHelper.h"

SASPlan SASParser::Parse(std::filesystem::path path) {
    std::ifstream stream(path);
    std::string content( (std::istreambuf_iterator<char>(stream) ),
                       (std::istreambuf_iterator<char>()    ) );
    return Parse(content);
}

SASPlan SASParser::Parse(std::string SAS) {
    std::vector<SASAction> actions;
    int cost;
    std::stringstream ss(SAS);
    std::string line;
    while (std::getline(ss, line)) {
        line = StringHelper::Trim(line);
        StringHelper::RemoveCharacter(&line, ')');
        StringHelper::RemoveCharacter(&line, '(');
        if (line[0] == ';') {
            cost = ParseCost(line);
        } else {
            SASAction newAction = ParseAction(line);
            actions.push_back(newAction);
        }
    }
    return SASPlan(actions, cost);
}

std::vector<std::string> tokenize(std::string const &str, const char delim) {
    std::stringstream ss(str);
    std::vector<std::string> tokens;
 
    std::string s;
    while (std::getline(ss, s, delim)) {
        tokens.push_back(s);
    }
    return tokens;
}

SASAction SASParser::ParseAction(std::string line) {
    StringHelper::RemoveCharacter(&line, '\r');
    StringHelper::RemoveCharacter(&line, '\n');
    std::vector<std::string> tokens = tokenize(line, ' ');
    std::string actionName = tokens.front(); tokens.erase(tokens.begin());
    std::vector<std::string> parameters = tokens;
    return SASAction(actionName, parameters);
}

int SASParser::ParseCost(std::string line) {
    int equalityIndex = line.find('=');
    if (equalityIndex == line.npos)
        return -1;
    line = line.substr(equalityIndex + 1);
    while (line.length() > 0 && !isdigit(line[0]))
        line = line.substr(1);
    
    std::string strInt = "";
    while (line.length() > 0 && isdigit(line[0])) {
        strInt += line[0];
        line = line.substr(1);
    }
    return std::atoi(strInt.c_str());
}