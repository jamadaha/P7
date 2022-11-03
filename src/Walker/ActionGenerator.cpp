// PseudoCode
    // Action generation is split into 4 parts.
    // 1. Candidate Objects
    // 2. Candidate Pairs
    // 3. Permutation Generation
    // 4. Multifact Verification
    //
    // Candidate Objects
    // -----------------
    // Premise
        // For a given action find all objects for each parameter which fulfill all unary facts.
    // Algorithm
        // Input
            // The given action A, which includes: parameters P and preconditions Pre (Which includes what precondition index I it relates to)
            // The current state S, which includes: objects O and unary facts UF
        // Output 
            // A set of objects for each paramter p in P.
        // Procedure
            // Set CO = Empty list
            // For every parem in A
                // Set O = S.O
                // For every pre in A preconditions, where argument count == 1
                    // if pre value == true
                        // Set O = O intersect UF.(A.I)
                    // else 
                        // Set O = O - UF.(A.I)
                // Append O to CO
            // Return CO
    //
    // Candidate Pairs
    // -----------------
    // Premise
        // Given a list of candidate objects sets, generate valid pairings according to binary facts
        // I.e. these objects of parameter 1 are valid in combination with these of parameter 3
    // Algorithm
        // Input: 
            // Binary action preconditions Pre, i.e. preconditions of the action with only 2 arguments
            // The current state S,
            // Candidate objects CO
        // Output: A set of valid combinations for each pair of indexes
        // Procedure:
            // CM = Empty map from an index pair, to candidate pairs, e.g. (0, 1) -> ((0, 0), (0, 1), (0, 2))
            //                                                        i.e. For the given set of parameter indexes, these pairings of candidate objects are legal
            // For every pre in Pre
                // CP = Empty set
                // For every o1 in CO[pre[0]], i.e. get object o1 from candidate objects at the first argument of the precondition
                    // For every o2 in CO[pre[1]]
                        // if (S contains fact (o1, o2)) == pre value
                            // Add (o1, o2) to CP  
                // if CM[(pre[0], pre[1])] = Empty set
                    // CM[(pre[0], pre[1])] = CP
                // else, Note: This only happens if two preconditions have the same arguments, e.g. pre_1: ?x ?y, pre_2: ?x ?y
                    // CP intersect CM[(pre[0], pre[1])]
            // return CM
    //
    // Permutation Generation
    // -----------------
    // Premise
        // Take the candidate objects and pairs, ande generate all legal permutations
    // Algorithm
        // Input: Candidate objects CO, candidate pairs CP, permutation p (Starts off empty, but is filled through recursion), permutations P (Set of valid permutations, initially empty)
        // Output: It outputs through the parameter P
        // Procedure - Permute:
            // Set p = empty list, i.e. working permutation
            // for every object o in CO[p.length]
                // Append o to p
                // Set validPerm = true
                // for every i = 0 to p.length
                    // if CP contains (i, p.length) and cp[(i, p.length)] !contains (p[i], p[p.size])
                        // validPerm = false
                // if validPerm
                    // if p.size = CO.size
                        // P append p
                    // else
                        // Permute(CO, CP, p)
                // Pop o from p
    //
    // Multifact Verification
    // -----------------
    // Premise
    // Check whether a given permutation is valid
    // 
    // Algorithm
        // Input: Given a permutation p, a set of multi fact preconditions Pre, and a set of multi facts MF (Any predicate with over 2 arguments)
        // Output: true/false
        // Procedure:
            // for every pre in Pre
                // if MF !contains (p[pre[0]], p[pre[1]], ..., p[pre[Pre.count]])
                    // return false
            // return true


#include "ActionGenerator.hpp"

using namespace std;

vector<PDDLActionInstance> ActionGenerator::GenerateActions(const PDDLState *state) {
    vector<PDDLActionInstance> legalActions;
    const int domainLength = domain->actions.size();
    for (int i = 0; i < domainLength; i++) {
        vector<PDDLActionInstance> tempActions = GenerateActions(&(domain->actions[i]), state);
        copy(tempActions.begin(), tempActions.end(), back_inserter(legalActions));
    }
    totalActions += legalActions.size();
    return legalActions;
}

vector<PDDLActionInstance> ActionGenerator::GenerateActions(const PDDLAction *action, const PDDLState *state) const {
    vector<PDDLActionInstance> legalActions;

    // Object which fulfill the unary literals of the action preconditions
    vector<unordered_set<unsigned int>> candidateObjects;
    candidateObjects.reserve(action->parameters.size());
    if (!GetCandidateObjects(candidateObjects, action, state))
        return legalActions;
    
    unordered_map<pair<unsigned int, unsigned int>, unordered_set<pair<unsigned int, unsigned int>>> candidatePairs;
    for (int i = 0; i < action->preconditions.size(); i++) {
        auto precondition = &action->preconditions.at(i);
        if (precondition->args.size() != 2)
            continue;
        
        auto indexPair = make_pair(precondition->args.at(0), precondition->args.at(1));

        auto pairs = unordered_set<pair<unsigned int, unsigned int>>();
        auto indexFirsts = unordered_set<unsigned int>();
        auto indexSecond = unordered_set<unsigned int>();
        for (auto iter = candidateObjects.at(indexPair.first).begin(); iter != candidateObjects.at(indexPair.first).end(); iter++) {
            for (auto iter2 = candidateObjects.at(indexPair.second).begin(); iter2 != candidateObjects.at(indexPair.second).end(); iter2++) {
                auto pair = make_pair(*iter, *iter2);
                if (state->ContainsFact(precondition->predicateIndex, pair) == precondition->value) {
                    pairs.emplace(pair);
                    indexFirsts.emplace(pair.first);
                    indexSecond.emplace(pair.second);
                }
            }
        }
        if (pairs.size() == 0)
            return legalActions;

        if (!candidatePairs.contains(indexPair)) {
            candidatePairs[indexPair] = pairs;
            // Remove those from candidate objects which are not in any pairs
            Algorithms::Intersect(candidateObjects.at(indexPair.first), indexFirsts);
            Algorithms::Intersect(candidateObjects.at(indexPair.second), indexSecond);
        } else {
            // This happens if two preconditions have the same index pair, i.e. pre1: ?x, ?y & pre2: ?x, ?y
            // In this case the legal pairs is the intersection between the two
            Algorithms::Intersect(candidatePairs.at(indexPair), pairs);
        }
    }

    std::vector<std::vector<unsigned int>> candidatePermutations;
    if (candidateObjects.size() == 1) {
        for (auto iter = candidateObjects.at(0).begin(); iter != candidateObjects.at(0).end(); iter++)
            candidatePermutations.push_back({ *iter });
    } else
        candidatePermutations = PermuteAll(candidateObjects, candidatePairs);
        
    for (int i = 0; i < candidatePermutations.size(); i++)
        if (IsLegal(&action->preconditions, state, &candidatePermutations.at(i)))
            legalActions.push_back(PDDLActionInstance(action, candidatePermutations.at(i)));
 
    return legalActions;
}

bool ActionGenerator::GetCandidateObjects(vector<unordered_set<unsigned int>> &candidateObjects, const PDDLAction *action, const PDDLState *state) const {
    const int parameterLength = action->parameters.size();
    for (int i = 0; i < parameterLength; i++) {
        std::unordered_set<unsigned int> tempCandididateObjects = GetCandidateObjects(&action->applicableUnaryLiterals.at(i), state);
        // if some parameter doesn't have any candidate object, the action is not possible
        if (tempCandididateObjects.size() == 0)
            return false;
        candidateObjects.push_back(tempCandididateObjects);
    }
    return true;
}

// Assumes atleast 1 literal
unordered_set<unsigned int> ActionGenerator::GetCandidateObjects(const unordered_set<const PDDLLiteral*> *literals, const PDDLState *state) const {
    unordered_set<unsigned int> candidateObjects;

    for (auto iter = literals->begin(); iter != literals->end(); iter++)
        if ((*iter)->value == true) {
            candidateObjects = state->unaryFacts.at((*iter)->predicateIndex);
            break;
        }

    if (candidateObjects.size() == 0) {
        candidateObjects.reserve(problem->objects.size());
        for (int i = 0; i < problem->objects.size(); i++)
            candidateObjects.emplace(i);
    }
    
    RemoveIllegal(candidateObjects, literals, state);

    return candidateObjects;
}

void ActionGenerator::RemoveIllegal(std::unordered_set<unsigned int> &set, const std::unordered_set<const PDDLLiteral*> *literals, const PDDLState *state) {
    for (auto literal = literals->begin(); literal != literals->end(); literal++)
        if ((*literal)->value)
            Algorithms::Intersect(set, state->unaryFacts.at((*literal)->predicateIndex));
        else
            Algorithms::Difference(set, state->unaryFacts.at((*literal)->predicateIndex));
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
        for (int i = 0; i < permutation->size() - 1; i++) {
            auto pair = make_pair(i, permutation->size() - 1);
            if (candidatePairs.contains(pair) && (!candidatePairs.at(pair).contains(make_pair(permutation->at(pair.first), permutation->at(pair.second))))) {
                validPerm = false;
                break;
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

bool ActionGenerator::IsLegal(const vector<PDDLLiteral> *literals, const PDDLState *state, const vector<unsigned int> *objects) {
    for (auto iter = literals->begin(); iter != literals->end(); iter++) {
        if ((*iter).args.size() < 3)
            continue;
        if (!state->ContainsFact((*iter).predicateIndex, &(*iter).args, objects))
            return false;
    }
    return true;
}
