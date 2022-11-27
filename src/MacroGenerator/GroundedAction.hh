#ifndef GROUNDED_ACTION
#define GROUNDED_ACTION

#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

#include "../Helpers/Hashes.hh"

// Similar to PDDL::Literal, except that it doesn't use indexes, nor does it store the value
struct GroundedLiteral {
    const unsigned int predicate;
    const std::vector<unsigned int> objects;
    GroundedLiteral(unsigned int predicate, std::vector<unsigned int> objects) : predicate(predicate), objects(objects) {};

    friend bool operator==(const GroundedLiteral& lhs, const GroundedLiteral& rhs) {
        return (lhs.predicate == rhs.predicate && lhs.objects == rhs.objects);
    }
};

template<> struct std::hash<GroundedLiteral> {
    std::size_t operator()(GroundedLiteral const& s) const noexcept {
        std::size_t h1 = std::hash<unsigned int>{}(s.predicate);
        std::size_t h2 = std::hash<std::vector<unsigned int>>{}(s.objects);
        return h1 ^ (h2 << 1); // or use boost::hash_combine (see Discussion) https://en.cppreference.com/w/Talk:cpp/utility/hash
    }
};

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

#endif
