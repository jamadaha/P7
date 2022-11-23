#include "Parser.hh"

using namespace std;
using namespace SAS;

Plan Parser::Parse(filesystem::path path) {
    ifstream stream(path);
    string content( (istreambuf_iterator<char>(stream) ),
                       (istreambuf_iterator<char>()    ) );
    stream.close();
    return Parse(content);
}

Plan Parser::Parse(string SAS) {
    vector<Action> actions;
    int cost;
    stringstream ss(SAS);
    string line;
    while (getline(ss, line)) {
        line = StringHelper::Trim(line);
        StringHelper::RemoveCharacter(&line, ')');
        StringHelper::RemoveCharacter(&line, '(');
        if (line[0] == ';') {
            cost = ParseCost(line);
        } else {
            Action newAction = ParseAction(line);
            actions.push_back(newAction);
        }
    }
    return Plan(actions, cost, 0);
}

vector<string> tokenize(string const &str, const char delim) {
    stringstream ss(str);
    vector<string> tokens;
 
    string s;
    while (getline(ss, s, delim)) {
        tokens.push_back(s);
    }
    return tokens;
}

Action Parser::ParseAction(string line) {
    StringHelper::RemoveCharacter(&line, '\r');
    StringHelper::RemoveCharacter(&line, '\n');
    vector<string> tokens = tokenize(line, ' ');
    string actionName = tokens.front(); tokens.erase(tokens.begin());
    vector<string> parameters = tokens;
    return Action(actionName, parameters);
}

int Parser::ParseCost(string line) {
    int equalityIndex = line.find('=');
    if (equalityIndex == line.npos)
        return -1;
    line = line.substr(equalityIndex + 1);
    while (line.length() > 0 && !isdigit(line[0]))
        line = line.substr(1);
    
    string strInt = "";
    while (line.length() > 0 && isdigit(line[0])) {
        strInt += line[0];
        line = line.substr(1);
    }
    return atoi(strInt.c_str());
}