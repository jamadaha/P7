#ifndef SAS_ACTION_HH
#define SAS_ACTION_HH

#include <string>
#include <vector>

namespace SAS {
    struct Action {
        std::string name;
        std::vector<std::string> parameters;

        Action(std::string name, std::vector<std::string> parameters) : name(name), parameters(parameters) {}
    };
}

#endif
