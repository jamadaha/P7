#include "Config.hh"

using namespace std;

#pragma region GetNewItem Templates

template <typename T>
T Config::GetNewItem(string value) {
    return T();
}

template <>
int Config::GetNewItem(string value) {
    return stoi(value);
}

template <>
double Config::GetNewItem(string value) {
    return stod(value);
}

template <>
bool Config::GetNewItem(string value) {
    for_each(value.begin(), value.end(), [](char& c) {
        c = ::toupper(c);
        });
    if (value == "TRUE")
        return true;
    else if (value == "FALSE")
        return false;
    return false;
}

template <>
string Config::GetNewItem(string value) {
    return value;
}

template <>
filesystem::path Config::GetNewItem(string value) {
    return filesystem::path(value);
}

#pragma endregion

#pragma region GetItem Templates

template <typename T>
T Config::GetItem(string name) {
    if (items.contains(name))
        return *((T*)items.at(name));
    ConsoleHelper::PrintWarning("Key " + name + " was not found!");
    return T();
}

template string Config::GetItem<string>(string name);
template bool Config::GetItem<bool>(string name);
template int Config::GetItem<int>(string name);
template double Config::GetItem<double>(string name);
template filesystem::path Config::GetItem<filesystem::path>(string name);
template vector<string> Config::GetItem<vector<string>>(string name);

#pragma endregion

#pragma region GetNewListItem Templates

template <typename T>
vector<T> Config::GetNewListItem(vector<string> values) {
    vector<T> newList;
    for (auto i : values)
        newList.push_back(GetNewItem<T>(i));
    return newList;
}

#pragma endregion

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

    string typeNameStr = GetTypeName(line);
    string name = GetName(line);
    string value = GetStringValue(line);

    if (typeNameStr.starts_with("LIST")) {
        string subTypeStr = GetSubTypeName(typeNameStr);
        auto subType = GetTypeEnum(subTypeStr);

        auto list = StringHelper::Split(value, ',');

        switch (subType)
        {
        case Config::NONE:
            throw invalid_argument("Invalid config type!");
            break;
        case Config::INT:
            items.emplace(name, new vector<int>(GetNewListItem<int>(list)));
            break;
        case Config::DOUBLE:
            items.emplace(name, new vector<double>(GetNewListItem<double>(list)));
            break;
        case Config::BOOL:
            items.emplace(name, new vector<bool>(GetNewListItem<bool>(list)));
            break;
        case Config::STRING:
            items.emplace(name, new vector<string>(GetNewListItem<string>(list)));
            break;
        case Config::PATH:
            items.emplace(name, new vector<filesystem::path>(GetNewListItem<filesystem::path>(list)));
            break;
        default:
            throw invalid_argument("Invalid config type!");
            break;
        }
    }
    else {
        auto typeName = GetTypeEnum(typeNameStr);

        switch (typeName)
        {
        case Config::NONE:
            throw invalid_argument("Invalid config type!");
            break;
        case Config::INT:
            items.emplace(name, new int(GetNewItem<int>(value)));
            break;
        case Config::DOUBLE:
            items.emplace(name, new double(GetNewItem<double>(value)));
            break;
        case Config::BOOL:
            items.emplace(name, new bool(GetNewItem<bool>(value)));
            break;
        case Config::STRING:
            items.emplace(name, new string(GetNewItem<string>(value)));
            break;
        case Config::PATH:
            items.emplace(name, new filesystem::path(GetNewItem<filesystem::path>(value)));
            break;
        default:
            throw invalid_argument("Invalid config type!");
            break;
        }
    }
}

Config::ValidTypes Config::GetTypeEnum(std::string typeName) {
    if (typeName == "INT") {
        return Config::ValidTypes::INT;
    }
    else if (typeName == "DOUBLE") {
        return Config::ValidTypes::DOUBLE;
    }
    else if (typeName == "BOOL") {
        return Config::ValidTypes::BOOL;
    }
    else if (typeName == "STRING") {
        return Config::ValidTypes::STRING;
    }
    else if (typeName == "PATH") {
        return Config::ValidTypes::PATH;
    }
    return Config::ValidTypes::NONE;
}

string Config::GetTypeName(string line) {
    string typeName = line.substr(0, line.find(":"));
    typeName = StringHelper::Trim(typeName);
    typeName = StringHelper::ToUpper(typeName);
    return typeName;
}

string Config::GetSubTypeName(string typeName) {
    string subType = typeName.substr(typeName.find("<") + 1);
    subType = StringHelper::RemoveCharacter(subType, '>');
    subType = StringHelper::Trim(subType);
    subType = StringHelper::ToUpper(subType);
    return subType;
}

string Config::GetName(string line) {
    string name = line.substr(line.find(":") + 1);
    name = name.substr(0, name.find("="));
    name = StringHelper::Trim(name);
    return name;
}

string Config::GetStringValue(string line) {
    string value = line.substr(line.find("=") + 1);
    value = StringHelper::Trim(value);
    return value;
}

bool Config::Contains(string name) {
    return items.contains(name);
}

void Config::Clear() {
    for (auto i : items) {
        free(i.second);
    }
    items.clear();
}