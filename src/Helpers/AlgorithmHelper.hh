#ifndef ALGORITHM_HELPER
#define ALGORITHM_HELPER

#include <vector>
#include <unordered_set>
#include <iterator>

#include "Hashes.hh"

class AlgorithmHelper {
public:
    template<typename T>
    static void InsertAll(std::unordered_set<T> &a, const std::unordered_set<T>& b) {
        for (auto iter = b.begin(); iter != b.end(); iter++)
            a.emplace((*iter));
    }
    template<typename T>
    static void InsertAll(std::vector<T> &a, const std::vector<T> &b) {
        for (auto iter = b.begin(); iter != b.end(); iter++)
            a.push_back((*iter));
    }
    static void Intersect(std::unordered_set<unsigned int> &a, const std::unordered_set<unsigned int> &b);
    static void Intersect(std::unordered_set<std::pair<unsigned int, unsigned int>> &a, const std::unordered_set<std::pair<unsigned int, unsigned int>> &b);
    static void Difference(std::unordered_set<unsigned int> &a, const std::unordered_set<unsigned int> &b);
    static void Difference(std::unordered_set<std::pair<unsigned int, unsigned int>> &a, const std::unordered_set<std::pair<unsigned int, unsigned int>> &b);

    template<typename T>
    static std::vector<T> Reverse(std::vector<T> &a) {
        std::vector<T> tempVector;
        tempVector.reserve(a.size());
        for (int i = a.size() - 1; i >= 0; i--)
            tempVector.push_back(a.at(i));
        return tempVector;
    }

    static unsigned int Median(std::vector<unsigned int> v);

    static unsigned int Average(std::vector<unsigned int> v);
};

#endif
