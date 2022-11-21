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

    array<unsigned int, MAXPARAMSIZE> parentValues;
    parentValues.fill(-1);
    set<array<unsigned int, MAXPARAMSIZE>> initialCandidates = GetCandidates(state, parentValues, 0, action->parameters.size());

    for (auto candidate : initialCandidates)
        legalActions.push_back(PDDLActionInstance(action, vector<unsigned int> (candidate.begin(), candidate.begin() + action->parameters.size())));

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

set<array<unsigned int, MAXPARAMSIZE>> ActionGenerator2::GetCandidates(const PDDLState* state, array<unsigned int, MAXPARAMSIZE> parentValues, const int currentIndex, const int maxIndex) {
    set<array<unsigned int, MAXPARAMSIZE>> newSet;
    vector<unsigned int> candidates;
    for (auto precon = (&UnaryActionLiterals)->begin(); precon != (&UnaryActionLiterals)->end(); precon++) {
        if (precon->args.at(0) == currentIndex) {
            if (candidates.size() == 0) {
                for (auto fact : state->unaryFacts.at(precon->predicateIndex)) {
                    if (!Contains(parentValues, fact, currentIndex)) {
                        candidates.push_back(fact);
                    }
                }
            }
            else
            {
                for (int i = 0; i < candidates.size(); i++) {
                    if (!state->unaryFacts.at(precon->predicateIndex).contains(candidates.at(i))) {
                        candidates.erase(candidates.begin() + i);
                        i--;
                    }
                }
            }
        }
    }

    for (auto candidate : candidates) {
        array<unsigned int, MAXPARAMSIZE> newArray = parentValues;
        newArray.at(currentIndex) = candidate;

        if (IsBinaryLegal(state, &newArray, currentIndex)) {
            if (currentIndex + 1 == maxIndex)
                newSet.emplace(newArray);
            else {
                set<array<unsigned int, MAXPARAMSIZE>> returnSet = GetCandidates(state, newArray, currentIndex + 1, maxIndex);
                for (auto returnValues : returnSet)
                    newSet.emplace(returnValues);
            }
        }
    }


    return newSet;
}

bool ActionGenerator2::Contains(const array<unsigned int, MAXPARAMSIZE> values, const unsigned int value, const int limit) {
    for (int i = 0; i < limit; i++)
        if (values.at(i) == value)
            return true;
    return false;
}

bool ActionGenerator2::IsBinaryLegal(const PDDLState* state, array<unsigned int, MAXPARAMSIZE>* set, const int currentMax) {
    for (auto precon = (&BinaryActionLiterals)->begin(); precon != (&BinaryActionLiterals)->end(); precon++) {
        int arg1 = precon->args.at(0);
        int arg2 = precon->args.at(1);
        if (arg1 <= currentMax && arg2 <= currentMax) 
            if (!state->binaryFacts.at(precon->predicateIndex).contains(make_pair(set->at(arg1), set->at(arg2)))) 
                return false;
    }
    return true;
}

bool ActionGenerator2::IsUnaryLegal(const PDDLState* state, array<unsigned int, MAXPARAMSIZE>* set, const int currentMax) {
    for (auto precon = (&UnaryActionLiterals)->begin(); precon != (&UnaryActionLiterals)->end(); precon++) {
        int arg1 = precon->args.at(0);
        if (arg1 <= currentMax)
            if (!state->unaryFacts.at(precon->predicateIndex).contains(set->at(arg1)))
                return false;
    }
    return true;
}
