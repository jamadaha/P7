#include "Algorithms.hh"

void Algorithms::Intersect(std::unordered_set<unsigned int> &a, const std::unordered_set<unsigned int> &b) {
    const auto Contains = [&](auto const& x) { return !b.contains(x);};
    std::erase_if(a, Contains);
}

void Algorithms::Intersect(std::unordered_set<std::pair<unsigned int, unsigned int>> &a, const std::unordered_set<std::pair<unsigned int, unsigned int>> &b) {
    const auto Contains = [&](auto const& x) { return !b.contains(x);};
    std::erase_if(a, Contains);
}

void Algorithms::Difference(std::unordered_set<unsigned int> &a, const std::unordered_set<unsigned int> &b) {
    const auto Contains = [&](auto const& x) { return b.contains(x);};
    std::erase_if(a, Contains);
}

void Algorithms::Difference(std::unordered_set<std::pair<unsigned int, unsigned int>> &a, const std::unordered_set<std::pair<unsigned int, unsigned int>> &b) {
    const auto Contains = [&](auto const& x) { return b.contains(x);};
    std::erase_if(a, Contains);
}