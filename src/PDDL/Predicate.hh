#ifndef PDDL_PREDICATE_HH
#define PDDL_PREDICATE_HH

#include <string>
#include <vector>

namespace PDDL {
    struct Predicate {
        const std::string name;
        // This is only used for later printing
        const std::vector<std::string> arguments;
        const int argumentCount;

        Predicate(int argumentCount) : argumentCount(argumentCount) {};
        Predicate(std::string name, int argumentCount) : name(name), argumentCount(argumentCount), arguments(std::vector<std::string>{ "?x" }) {};
        Predicate(std::string name, std::vector<std::string> arguments, int argumentCount) : name(name), arguments(arguments), argumentCount(argumentCount) {};
    };
}

#endif
