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
    set<array<unsigned int, MAXPARAMSIZE>> initialCandidates;
    GetCandidates(&initialCandidates, state, parentValues, 0, action->parameters.size());

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

void ActionGenerator2::GetCandidates(set<array<unsigned int, MAXPARAMSIZE>>* candidates, const PDDLState* state, array<unsigned int, MAXPARAMSIZE> parentValues, const int currentIndex, const int maxIndex) {
    unordered_set<unsigned int> objectCandidates;
    for (auto precon = (&UnaryActionLiterals)->begin(); precon != (&UnaryActionLiterals)->end(); precon++) {
        if (precon->args.at(0) == currentIndex) {
            if (objectCandidates.size() == 0) {
                for (auto fact : state->unaryFacts.at(precon->predicateIndex))
                    if (!Contains(parentValues, fact, currentIndex))
                        objectCandidates.emplace(fact);
            }
            else {
                for (auto candidate = objectCandidates.begin(); candidate != objectCandidates.end(); candidate++)
                    if (!state->unaryFacts.at(precon->predicateIndex).contains(*candidate))
                        objectCandidates.erase(*candidate);
            }
        }
    }

    for (auto candidate : objectCandidates) {
        array<unsigned int, MAXPARAMSIZE> newArray = parentValues;
        newArray.at(currentIndex) = candidate;

        if (IsBinaryLegal(state, &newArray, currentIndex)) {
            if (currentIndex + 1 == maxIndex)
                candidates->emplace(newArray);
            else
                GetCandidates(candidates, state, newArray, currentIndex + 1, maxIndex);
        }
    }
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
