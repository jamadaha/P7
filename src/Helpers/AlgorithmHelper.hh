#ifndef ALGORITHM_HELPER
#define ALGORITHM_HELPER

#include <vector>
#include <unordered_set>
#include <iterator>

#include "Hashes.hh"

class AlgorithmHelper {
public:
    static void Intersect(std::unordered_set<unsigned int> &a, const std::unordered_set<unsigned int> &b);
    static void Intersect(std::unordered_set<std::pair<unsigned int, unsigned int>> &a, const std::unordered_set<std::pair<unsigned int, unsigned int>> &b);
    static void Difference(std::unordered_set<unsigned int> &a, const std::unordered_set<unsigned int> &b);
    static void Difference(std::unordered_set<std::pair<unsigned int, unsigned int>> &a, const std::unordered_set<std::pair<unsigned int, unsigned int>> &b);
};

#endif