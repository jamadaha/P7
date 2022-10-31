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
private:
    template <typename T>
    T GetNewItem(std::string value);

    std::map<std::string, void*> items;
};

#endif
