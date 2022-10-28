#include "Config.hh"

using namespace std;

void Config::ParseConfigFile(filesystem::path path) {
    ifstream stream(path);
    string content((istreambuf_iterator<char>(stream)),
        (istreambuf_iterator<char>()));
    stream.close();

    stringstream ss(content);
    string line;
    while (getline(ss, line)) {
        ParseConfigItem(line);
    }
}

void Config::ParseConfigItem(std::string line) {
    line = StringHelper::Trim(line);
    if (line.starts_with(";"))
        return;
    if (line == "")
        return;

    string typeName = line.substr(0, line.find(":"));
    typeName = StringHelper::Trim(typeName);
    string name = line.substr(line.find(":") + 1);
    name = name.substr(0, name.find("="));
    name = StringHelper::Trim(name);
    string value = line.substr(line.find("=") + 1);
    value = StringHelper::Trim(value);

    for_each(typeName.begin(), typeName.end(), [](char& c) {
        c = ::toupper(c);
        });

    if (typeName == "INT") {
        int num = stoi(value);
        intItems.emplace(name, num);
    }
    else if (typeName == "DOUBLE") {
        double num = stod(value);
        doubleItems.emplace(name, num);
    }
    else if (typeName == "BOOL") {
        for_each(value.begin(), value.end(), [](char& c) {
            c = ::toupper(c);
            });
        if (value == "TRUE")
            boolItems.emplace(name, true);
        else if (value == "FALSE")
            boolItems.emplace(name, false);
    }
    else if (typeName == "STRING") {
        stringItems.emplace(name, value);
    }
    else if (typeName == "PATH") {
        pathItems.emplace(name, filesystem::path(value));
    }
}

int Config::GetInteger(string name) {
    if (!intItems.contains(name)) {
        ConsoleHelper::PrintWarning("Key " + name + " was not found!");
        return 0;
    }
    return intItems.at(name);
}

double Config::GetDouble(string name) {
    if (!doubleItems.contains(name)) {
        ConsoleHelper::PrintWarning("Key " + name + " was not found!");
        return 0;
    }
    return doubleItems.at(name);
}

bool Config::GetBool(string name) {
    if (!boolItems.contains(name)) {
        ConsoleHelper::PrintWarning("Key " + name + " was not found!");
        return false;
    }
    return boolItems.at(name);
}

string Config::GetString(string name) {
    if (!stringItems.contains(name)) {
        ConsoleHelper::PrintWarning("Key " + name + " was not found!");
        return "";
    }
    return stringItems.at(name);
}

filesystem::path Config::GetPath(string name) {
    if (!pathItems.contains(name)) {
        ConsoleHelper::PrintWarning("Key " + name + " was not found!");
        return "";
    }
    return pathItems.at(name);
}
