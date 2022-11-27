#ifndef PDDL_LITERAL_HH
#define PDDL_LITERAL_HH

#include <vector>

#include "../Helpers/Hashes.hh"

namespace PDDL {
    struct Literal {
        // Index of domain predicate list
        const unsigned int predicateIndex;
        // What parameter index of action the given argument position refers to
        const std::vector<unsigned int> args;
        // What value the predicate should be with the given arguments
        const bool value;
        Literal(unsigned int predicateIndex, std::vector<unsigned int> args, bool value) :
            predicateIndex(predicateIndex), args(args), value(value) {};

        /// @return Returns true if the predicateIndex and arguments are the same, ignores value
        friend bool operator==(const Literal& lhs, const Literal& rhs) {
            if (lhs.predicateIndex != rhs.predicateIndex)
                return false;
            if (lhs.args != rhs.args)
                return false;
            return true;
        }
    };
}

namespace std {
    template <>
    struct hash<PDDL::Literal> {
        auto operator()(const PDDL::Literal& s) const -> size_t {
            std::size_t h1 = hash<unsigned int>{}(s.predicateIndex);
            std::size_t h2 = hash<vector<unsigned int>>{}(s.args);
            return h1 ^ (h2 << 1);
        }
    };
}

#endif
