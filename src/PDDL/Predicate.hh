#ifndef PDDL_PREDICATE_HH
#define PDDL_PREDICATE_HH

#include <string>
#include <vector>

namespace PDDL {
    struct Predicate {
        const std::string name;
        const std::vector<std::string> arguments;
        const int argumentCount;

        Predicate(std::string name, std::vector<std::string> arguments, int argumentCount) : name(name), arguments(arguments), argumentCount(argumentCount) {};
    };
}

#endif
