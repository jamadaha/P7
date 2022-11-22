#include "ActionGenerator.hpp"

using namespace std;

vector<PDDLActionInstance> ActionGenerator::GenerateActions(const PDDLState *state) {
    vector<PDDLActionInstance> legalActions;
    for (auto iter = actions->begin(); iter != actions->end(); iter++) {
        vector<PDDLActionInstance> tempActions = GenerateActions(&(*iter), state);
        copy(tempActions.begin(), tempActions.end(), back_inserter(legalActions));
    }
    totalActions += legalActions.size();
    return legalActions;
}

vector<PDDLActionInstance> ActionGenerator::GenerateActions(const PDDLAction *action, const PDDLState *state) const {
    vector<PDDLActionInstance> legalActions;

    // Object which fulfill the unary literals of the action preconditions
    vector<unordered_set<unsigned int>> candidateObjects = unaryFactVerifier.GetLegalObjects(action, state);
    if (candidateObjects.size() != action->parameters.size())
        return legalActions;
    
    auto candidatePairs = binaryFactVerifier.GetLegalPairings(action, state, &candidateObjects);

    std::vector<std::vector<unsigned int>> candidatePermutations;
    if (candidateObjects.size() == 1) {
        for (auto iter = candidateObjects.at(0).begin(); iter != candidateObjects.at(0).end(); iter++)
            candidatePermutations.push_back({ *iter });
    } else
        candidatePermutations = PermuteAll(candidateObjects, candidatePairs);
        
    for (int i = 0; i < candidatePermutations.size(); i++)
        legalActions.push_back(PDDLActionInstance(action, candidatePermutations.at(i)));
 
    return legalActions;
}

std::vector<std::vector<unsigned int>> ActionGenerator::PermuteAll(std::vector<std::unordered_set<unsigned int>> candidateObjects, std::unordered_map<std::pair<unsigned int, unsigned int>, std::unordered_set<std::pair<unsigned int, unsigned int>>> candidatePairs) {
    vector<vector<unsigned int>> permutations;
    vector<unsigned int> permutation;
    permutation.reserve(candidateObjects.size());
    for (auto iter = candidateObjects.at(0).begin(); iter != candidateObjects.at(0).end(); iter++) {
        permutation.push_back(*iter);
        Permute(candidateObjects, candidatePairs, &permutations, &permutation);
        permutation.pop_back();
    }
    return permutations;
}

void ActionGenerator::Permute(std::vector<std::unordered_set<unsigned int>> &candidateObjects, std::unordered_map<std::pair<unsigned int, unsigned int>, std::unordered_set<std::pair<unsigned int, unsigned int>>> &candidatePairs, std::vector<std::vector<unsigned int>> *permutations, std::vector<unsigned int> *permutation) {
    for (auto iter = candidateObjects.at(permutation->size()).begin(); iter != candidateObjects.at(permutation->size()).end(); iter++) {
        permutation->push_back(*iter);

        bool validPerm = true;
        for (int i = 0; i < permutation->size(); i++) {
            for (int t = 0; t < permutation->size(); t++) {
                if (i != permutation->size() - 1 && t != permutation->size() - 1)
                    continue;
                auto pair = make_pair(i, t);
                if (candidatePairs.contains(pair) && (!candidatePairs.at(pair).contains(make_pair(permutation->at(pair.first), permutation->at(pair.second))))) {
                    validPerm = false;
                    break;
                }
            }
        }

        if (validPerm) {
            if (permutation->size() == candidateObjects.size())
                permutations->push_back(*permutation);
            else
                Permute(candidateObjects, candidatePairs, permutations, permutation);
        }
        permutation->pop_back();
    }
}
