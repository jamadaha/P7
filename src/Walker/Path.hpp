#ifndef PATH_TYPE
#define PATH_TYPE

#include <vector>

#include "../IntermediatePDDL/PDDLActionInstance.hh"

struct Path {
    std::vector<PDDLActionInstance> steps;
    Path(std::vector<PDDLActionInstance> steps) : steps(steps) {};
    Path(const Path &path) : steps(path.steps) {};

    friend bool operator==(const Path& lhs, const Path& rhs) {
        return lhs.steps == rhs.steps;
    }
};

namespace std {
    template <>
    struct hash<Path> {
        auto operator()(const Path& s) const -> size_t {
            std::size_t seed = s.steps.size();
            for (auto& i : s.steps) {
                seed ^= hash<PDDLActionInstance>{}(i)+0x9e3779b9 + (seed << 6) + (seed >> 2);
            }
            return seed;
        }
    };
}

#endif
