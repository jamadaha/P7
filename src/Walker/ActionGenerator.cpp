#include "ActionGenerator.hpp"

using namespace std;

// predicateLength -> (predicate -> (Fragment*))
// unordered_map<unsigned int, unordered_map<unsigned int, unordered_set<Fragment*>>> legalPredicateFragments;
// fragmentLength -> (Fragment)
// unordered_map<unsigned int, unordered_set<Fragment>> legalFragments;

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

bool Comp(pair<unsigned int, unsigned int> a, pair<unsigned int, unsigned int> b)
{
    return a < b;
}

vector<PDDLActionInstance> ActionGenerator::GenerateActions(const PDDLAction *action, const PDDLState *state) const {
    vector<PDDLActionInstance> legalActions;

    // Object which fulfill the unary literals of the action preconditions
    vector<unordered_set<unsigned int>> candidateObjects;
    candidateObjects.reserve(action->parameters.size());
    if (!GetCandidateObjects(candidateObjects, action, state))
        return legalActions;
    
    unordered_map<pair<unsigned int, unsigned int>, unordered_set<pair<unsigned int, unsigned int>>> candidatePairs;
    std::vector<unordered_set<pair<unsigned int, unsigned int>>> applicablePairs;
    applicablePairs.reserve(candidateObjects.size());
    for (int i = 0; i < candidateObjects.size(); i++)
        applicablePairs.push_back(unordered_set<pair<unsigned int, unsigned int>>());

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
                if (state->binaryFacts.at(precondition->predicateIndex).contains(pair) == precondition->value) {
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
            for (auto iter = candidatePairs.at(indexPair).begin(); iter != candidatePairs.at(indexPair).end(); iter++)
                applicablePairs.at(indexPair.first).emplace((*iter));
            // Remove those from candidate objects which are not in any pairs
            Intersect(candidateObjects.at(indexPair.first), indexFirsts);
            Intersect(candidateObjects.at(indexPair.second), indexSecond);
        } else {
            // This happens if two preconditions have the same index pair, i.e. pre1: ?x, ?y & pre2: ?x, ?y
            // In this case the legal pairs is the intersection between the two
            printf("NOT IMPLEMENTED");
        }
    }

    unordered_set<std::vector<unsigned int>> candidatePermutations;
    


    // Do something to handle multifacts
 
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

unordered_set<unsigned int> ActionGenerator::GetCandidateObjects(const unordered_set<const PDDLLiteral*> *literals, const PDDLState *state) const {
    if (literals->size() == 0) {
        const int objectCount = problem->objects.size();
        unordered_set<unsigned int> candidateObjects;
        candidateObjects.reserve(objectCount);
        for (int i = 0; i < problem->objects.size(); i++)
            candidateObjects.emplace(i);
        return candidateObjects;
    } else if (state->unaryFacts.size() > 0) {
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
    } else {
        return unordered_set<unsigned int>();
    }
}

void ActionGenerator::RemoveIllegal(std::unordered_set<unsigned int> &set, const std::unordered_set<const PDDLLiteral*> *literals, const PDDLState *state) {
    for (auto literal = literals->begin(); literal != literals->end(); literal++)
        RemoveIllegal(set, (*literal), state);
}

void ActionGenerator::RemoveIllegal(std::unordered_set<unsigned int> &set, const PDDLLiteral *literal, const PDDLState *state) {
    // Find intersection of candidateobjects and the new literal
    const std::unordered_set<unsigned int> *newObjectRef = &(state->unaryFacts.at(literal->predicateIndex));
    // Returns true, i.e. object should be deleted, depending on the literal state
    const auto NewObjectNegContains = [&](auto const& x) { return newObjectRef->contains(x) != literal->value; };
    // Remove those which are(n't) contained in both depending on literal value
    std::erase_if(set, NewObjectNegContains);
}

void ActionGenerator::Intersect(std::unordered_set<unsigned int> &a, const std::unordered_set<unsigned int> &b) {
    const auto Contains = [&](auto const& x) { return !b.contains(x);};
    std::erase_if(a, Contains);
}
