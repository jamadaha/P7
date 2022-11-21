#include "ActionGenerator2.hpp"

using namespace std;

vector<PDDLActionInstance> ActionGenerator2::GenerateActions(const PDDLState* state) {
    vector<PDDLActionInstance> legalActions;
    for (auto iter = actions->begin(); iter != actions->end(); iter++) {
        vector<PDDLActionInstance> tempActions = GenerateActions(&(*iter), state);
        copy(tempActions.begin(), tempActions.end(), back_inserter(legalActions));
    }
    totalActions += legalActions.size();
    return legalActions;
}

vector<PDDLActionInstance> ActionGenerator2::GenerateActions(const PDDLAction* action, const PDDLState* state) {
    vector<PDDLActionInstance> legalActions;

    unordered_set<vector<unsigned int>> candidates;
    if (action->preconditions.size() > 0) {
        if (action->preconditions.at(0).args.size() == 1) {
            if (state->unaryFacts.contains(action->preconditions.at(0).predicateIndex)) {
                for (auto fact : state->unaryFacts.at(action->preconditions.at(0).predicateIndex))
                    candidates.emplace(vector<unsigned int> { fact });
            }
        }
    }

    unordered_set<vector<unsigned int>> returnCandidates;
    for (auto candidate : candidates) {
        unordered_set<vector<unsigned int>> newCandidates = GetCandidates(action, state, candidate);
        for (auto newCandidate : newCandidates)
            if (newCandidate.size() == action->parameters.size())
                returnCandidates.emplace(newCandidate);
    }

    unordered_set<vector<unsigned int>> returnSet;
    for (auto checkSet : returnCandidates) {
        bool isOk = true;
        for (auto precon : action->preconditions) {
            if (precon.args.size() == 2) {
                if (!state->binaryFacts.at(precon.predicateIndex).contains(make_pair(checkSet.at(precon.args.at(0)), checkSet.at(precon.args.at(1))))) {
                    isOk = false;
                    break;
                }
            }
        }
        if (isOk)
            returnSet.emplace(checkSet);
    }

    for (auto candidate : returnSet)
        legalActions.push_back(PDDLActionInstance(action, candidate));

    return legalActions;
}

unordered_set<vector<unsigned int>> ActionGenerator2::GetCandidates(const PDDLAction* action, const PDDLState* state, vector<unsigned int> parentValues) {
    if (parentValues.size() >= action->parameters.size())
        return unordered_set<vector<unsigned int>>{parentValues};

    unordered_set<vector<unsigned int>> newSet;
    int paramIndex = parentValues.size();
    for (auto precon : action->preconditions) {
        if (precon.args.size() == 1) {
            if (precon.args.at(0) == paramIndex) {
                if (state->unaryFacts.contains(precon.predicateIndex)) {
                    for (auto fact : state->unaryFacts.at(precon.predicateIndex)) {
                        bool hasAny = false;
                        for (auto parent : parentValues)
                            if (fact == parent)
                                hasAny = true;
                        if (!hasAny) {
                            vector<unsigned int> newValues = parentValues;
                            newValues.push_back(fact);
                            unordered_set<vector<unsigned int>> returnSet = GetCandidates(action, state, newValues);
                            for (auto returnValues : returnSet)
                                newSet.emplace(returnValues);
                        }
                    }
                }
            }
        }
    }

    return newSet;
}
