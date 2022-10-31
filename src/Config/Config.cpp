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

    if (typeName.starts_with("LIST")) {
        string subType = typeName.substr(typeName.find("<"));
        subType = StringHelper::RemoveCharacter(subType, '>');

        auto list = StringHelper::Split(value, ',');

        if (subType == "INT") {
            vector<int> newList;
            for (auto i : list)
                newList.push_back(GetNewItem<int>(i));
            items.emplace(name, new vector<int>(newList));
        }
        else if (subType == "DOUBLE") {
            vector<double> newList;
            for (auto i : list)
                newList.push_back(GetNewItem<double>(i));
            items.emplace(name, new vector<double>(newList));
        }
        else if (subType == "BOOL") {
            vector<bool> newList;
            for (auto i : list)
                newList.push_back(GetNewItem<bool>(i));
            items.emplace(name, new vector<bool>(newList));
        }
        else if (subType == "STRING") {
            vector<string> newList;
            for (auto i : list)
                newList.push_back(GetNewItem<string>(i));
            items.emplace(name, new vector<string>(newList));
        }
        else if (subType == "PATH") {
            vector<filesystem::path> newList;
            for (auto i : list)
                newList.push_back(GetNewItem<filesystem::path>(i));
            items.emplace(name, new vector<filesystem::path>(newList));
        }
    }
    else {
        if (typeName == "INT") {
            items.emplace(name, new int(GetNewItem<int>(value)));
        }
        else if(typeName == "DOUBLE") {
            items.emplace(name, new double(GetNewItem<double>(value)));
        }
        else if(typeName == "BOOL") {
            items.emplace(name, new bool(GetNewItem<bool>(value)));
        }
        else if(typeName == "STRING") {
            items.emplace(name, new string(GetNewItem<string>(value)));
        }
        else if(typeName == "PATH") {
            items.emplace(name, new filesystem::path(GetNewItem<filesystem::path>(value)));
        }
    }

    //if (typeName == "INT") {
    //    int num = stoi(value);
    //    items.emplace(name, new int(num));
    //}
    //else if (typeName == "DOUBLE") {
    //    double num = stod(value);
    //    items.emplace(name, new double(num));
    //}
    //else if (typeName == "BOOL") {
    //    for_each(value.begin(), value.end(), [](char& c) {
    //        c = ::toupper(c);
    //        });
    //    if (value == "TRUE")
    //        items.emplace(name, new bool(true));
    //    else if (value == "FALSE")
    //        items.emplace(name, new bool(false));
    //}
    //else if (typeName == "STRING") {
    //    items.emplace(name, new string(value));
    //}
    //else if (typeName == "PATH") {
    //    items.emplace(name, new filesystem::path(value));
    //}
    //else if (typeName == "LIST<STRING>") {
    //    vector<string> newList;
    //    string delimiter = ",";

    //    size_t pos = 0;
    //    std::string token;
    //    while ((pos = value.find(delimiter)) != std::string::npos) {
    //        token = value.substr(0, pos);
    //        newList.push_back(token);
    //        value.erase(0, pos + delimiter.length());
    //    }
    //    newList.push_back(value);
    //    items.emplace(name, new vector<string>(newList));
    //}
}
