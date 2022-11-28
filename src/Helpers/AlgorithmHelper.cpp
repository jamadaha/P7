#include "AlgorithmHelper.hh"

void AlgorithmHelper::Intersect(std::unordered_set<unsigned int> &a, const std::unordered_set<unsigned int> &b) {
    const auto Contains = [&](auto const& x) { return !b.contains(x);};
    std::erase_if(a, Contains);
}

void AlgorithmHelper::Intersect(std::unordered_set<std::pair<unsigned int, unsigned int>> &a, const std::unordered_set<std::pair<unsigned int, unsigned int>> &b) {
    const auto Contains = [&](auto const& x) { return !b.contains(x);};
    std::erase_if(a, Contains);
}

void AlgorithmHelper::Difference(std::unordered_set<unsigned int> &a, const std::unordered_set<unsigned int> &b) {
    const auto Contains = [&](auto const& x) { return b.contains(x);};
    std::erase_if(a, Contains);
}

void AlgorithmHelper::Difference(std::unordered_set<std::pair<unsigned int, unsigned int>> &a, const std::unordered_set<std::pair<unsigned int, unsigned int>> &b) {
    const auto Contains = [&](auto const& x) { return b.contains(x);};
    std::erase_if(a, Contains);
}

unsigned int AlgorithmHelper::Median(std::vector<unsigned int> v) {
    if (v.size() == 0)
        return 0;
    size_t n = v.size() / 2;
    nth_element(v.begin(), v.begin() + n, v.end());
    return v[n];
}

unsigned int AlgorithmHelper::Average(std::vector<unsigned int> v) {
    if (v.size() == 0)
        return 0;
    unsigned int totalValue = 0;
    for (auto value : v)
        totalValue += value;
    return totalValue / v.size();
}
