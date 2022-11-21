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

    SetupActionLiteralsCache(action);

    unordered_set<vector<unsigned int>> initialCandidates = GetInitialParameterValue(state);

    unordered_set<vector<unsigned int>> finalCandidates;
    for (auto candidate : initialCandidates) {
        unordered_set<vector<unsigned int>> newCandidates = GetCandidates(state, candidate, action->parameters.size());
        for (auto newCandidate : newCandidates)
            if (newCandidate.size() == action->parameters.size())
                if (IsBinaryLegal(state, &newCandidate))
                    finalCandidates.emplace(newCandidate);
    }

    for (auto candidate : finalCandidates)
        legalActions.push_back(PDDLActionInstance(action, candidate));

    return legalActions;
}

void ActionGenerator2::SetupActionLiteralsCache(const PDDLAction* action) {
    UnaryActionLiterals.clear();
    BinaryActionLiterals.clear();
    for (auto predicate : action->preconditions) {
        if (predicate.args.size() == 1)
            UnaryActionLiterals.push_back(predicate);
        else if (predicate.args.size() == 2)
            BinaryActionLiterals.push_back(predicate);
    }
}

unordered_set<vector<unsigned int>> ActionGenerator2::GetInitialParameterValue(const PDDLState* state) {
    unordered_set<vector<unsigned int>> initialCandidates;
    for (auto precondition : UnaryActionLiterals) {
        if (state->unaryFacts.contains(precondition.predicateIndex)) {
            for (auto fact : state->unaryFacts.at(precondition.predicateIndex))
                initialCandidates.emplace(vector<unsigned int> { fact });
            break;
        }
    }
    return initialCandidates;
}

unordered_set<vector<unsigned int>> ActionGenerator2::GetCandidates(const PDDLState* state, vector<unsigned int> parentValues, const int maxIndex) {
    unordered_set<vector<unsigned int>> newSet;
    int paramIndex = parentValues.size();
    for (auto precon = (&UnaryActionLiterals)->begin(); precon != (&UnaryActionLiterals)->end(); precon++) {
        if (precon->args.at(0) == paramIndex) {
            if (state->unaryFacts.contains(precon->predicateIndex)) {
                for (auto fact : state->unaryFacts.at(precon->predicateIndex)) {
                    bool hasAny = false;
                    for (auto parent : parentValues) {
                        if (fact == parent)
                        {
                            hasAny = true;
                            break;
                        }
                    }
                    if (!hasAny) {
                        vector<unsigned int> newValues = parentValues;
                        newValues.push_back(fact);
                        if (IsBinaryLegal(state, &newValues)) {
                            if (newValues.size() == maxIndex) {
                                newSet.emplace(newValues);
                            }
                            else {
                                unordered_set<vector<unsigned int>> returnSet = GetCandidates(state, newValues, maxIndex);
                                for (auto returnValues : returnSet)
                                    newSet.emplace(returnValues);
                            }
                        }
                    }
                }
            }
        }
    }

    return newSet;
}

bool ActionGenerator2::IsBinaryLegal(const PDDLState* state, vector<unsigned int>* set) {
    for (auto precon = (&BinaryActionLiterals)->begin(); precon != (&BinaryActionLiterals)->end(); precon++) {
        int arg1 = precon->args.at(0);
        int arg2 = precon->args.at(1);
        if (arg1 < set->size() && arg2 < set->size()) {
            if (!state->binaryFacts.at(precon->predicateIndex).contains(make_pair(set->at(arg1), set->at(arg2)))) {
                return false;
            }
        }
    }
    return true;
}