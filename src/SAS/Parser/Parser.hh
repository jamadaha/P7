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

#include "../Plan.hh"
#include "../Helpers/StringHelper.hh"

namespace SAS {
    class Parser {
    public:
        Plan Parse(std::filesystem::path path);
        Plan Parse(std::string SAS);

    private:
        Action ParseAction(std::string line);
        int ParseCost(std::string line);
        std::vector<std::string> Tokenize(std::string const& str, const char delim);
    };
}

#endif
