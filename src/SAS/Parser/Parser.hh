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

#include "../SASPlan.hh"
#include "../Helpers/StringHelper.hh"

namespace SAS {
    class SASParser {
    public:
        SASPlan Parse(std::filesystem::path path);
        SASPlan Parse(std::string SAS);

    private:
        SASAction ParseAction(std::string line);
        int ParseCost(std::string line);
    };
}

#endif
