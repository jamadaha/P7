#ifndef CONFIG_HH
#define CONFIG_HH

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <filesystem>
#include <map>

#include "../Helpers/StringHelper.hh"
#include "../Helpers/ConsoleHelper.hh"

class Config {
public:
    void ParseConfigFile(std::filesystem::path path);
    void ParseConfigItem(std::string line);

    template <typename T>
    T GetItem(std::string name);

    bool Contains(std::string name);

    void Clear();
private:
    std::string GetTypeName(std::string line);
    std::string GetSubTypeName(std::string typeName);
    std::string GetName(std::string line);
    std::string GetStringValue(std::string line);

    template <typename T>
    T GetNewItem(std::string value);
    template <typename T>
    std::vector<T> GetNewListItem(std::vector<std::string> values);

    std::map<std::string, void*> items;
};

#endif
