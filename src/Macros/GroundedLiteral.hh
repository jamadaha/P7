#ifndef GROUNDED_LITERAL
#define GROUNDED_LITERAL

#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

#include "../Helpers/Hashes.hh"

namespace Macro {
    // Similar to PDDLLiteral, except that it doesn't use indexes, nor does it store the value
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
}

#endif
