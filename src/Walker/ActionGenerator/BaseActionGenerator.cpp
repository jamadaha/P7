#include "BaseActionGenerator.hpp"

using namespace std;

std::vector<std::vector<unsigned int>> BaseActionGenerator::PermuteAll(std::vector<std::unordered_set<unsigned int>> *candidateObjects, std::unordered_map<std::pair<unsigned int, unsigned int>, std::unordered_set<std::pair<unsigned int, unsigned int>>> *candidatePairs) {
    vector<vector<unsigned int>> permutations;
    vector<unsigned int> permutation;
    permutation.reserve(candidateObjects->size());
    for (auto iter = candidateObjects->at(0).begin(); iter != candidateObjects->at(0).end(); iter++) {
        permutation.push_back(*iter);
        Permute(candidateObjects, candidatePairs, &permutations, &permutation);
        permutation.pop_back();
    }
    return permutations;
}

void BaseActionGenerator::Permute(std::vector<std::unordered_set<unsigned int>> *candidateObjects, std::unordered_map<std::pair<unsigned int, unsigned int>, std::unordered_set<std::pair<unsigned int, unsigned int>>> *candidatePairs, std::vector<std::vector<unsigned int>> *permutations, std::vector<unsigned int> *permutation) {
    for (auto iter = candidateObjects->at(permutation->size()).begin(); iter != candidateObjects->at(permutation->size()).end(); iter++) {
        permutation->push_back(*iter);

        bool validPerm = true;
        for (int i = 0; i < permutation->size() - 1; i++) {
            auto pair = make_pair(i, permutation->size() - 1);
            if (candidatePairs->contains(pair) && (!candidatePairs->at(pair).contains(make_pair(permutation->at(pair.first), permutation->at(pair.second))))) {
                validPerm = false;
                break;
            }
        }

        if (validPerm) {
            if (permutation->size() == candidateObjects->size())
                permutations->push_back(*permutation);
            else
                Permute(candidateObjects, candidatePairs, permutations, permutation);
        }
        permutation->pop_back();
    }
}
