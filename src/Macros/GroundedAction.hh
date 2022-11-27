#ifndef GROUNDED_ACTION
#define GROUNDED_ACTION

#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

#include "../Helpers/Hashes.hh"
#include "GroundedLiteral.hh"

namespace Macros {
    struct GroundedAction {
        const std::string name;
        const std::unordered_set<unsigned int> parameters;
        const std::unordered_map<GroundedLiteral, bool> preconditions;
        const std::unordered_map<GroundedLiteral, bool> effects;
        GroundedAction(std::string name) : name(name) {};
        GroundedAction(std::string name,
            std::unordered_set<unsigned int> parameters,
            std::unordered_map<GroundedLiteral, bool> preconditions,
            std::unordered_map<GroundedLiteral, bool> effects) :
            name(name), parameters(parameters), preconditions(preconditions), effects(effects) {};
    };
}

#endif
