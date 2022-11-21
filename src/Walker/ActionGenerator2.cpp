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

    set<array<unsigned int, MAXPARAMSIZE>> initialCandidates = GetInitialParameterValue(state);

    set<array<unsigned int, MAXPARAMSIZE>> finalCandidates;
    for (auto candidate : initialCandidates) {
        set<array<unsigned int, MAXPARAMSIZE>> newCandidates = GetCandidates(state, candidate, 1, action->parameters.size());
        for (auto newCandidate : newCandidates)
            //if (newCandidate.size() == action->parameters.size())
                if (IsBinaryLegal(state, &newCandidate, action->parameters.size()))
                    finalCandidates.emplace(newCandidate);
    }

    for (auto candidate : finalCandidates)
        legalActions.push_back(PDDLActionInstance(action, vector<unsigned int> (candidate.begin(), candidate.end())));

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

set<array<unsigned int, MAXPARAMSIZE>> ActionGenerator2::GetInitialParameterValue(const PDDLState* state) {
    set<array<unsigned int, MAXPARAMSIZE>> initialCandidates;
    for (auto precondition : UnaryActionLiterals) {
        if (state->unaryFacts.contains(precondition.predicateIndex)) {
            for (auto fact : state->unaryFacts.at(precondition.predicateIndex))
                initialCandidates.emplace(array<unsigned int, MAXPARAMSIZE> { fact });
            break;
        }
    }
    return initialCandidates;
}

set<array<unsigned int, MAXPARAMSIZE>> ActionGenerator2::GetCandidates(const PDDLState* state, array<unsigned int, MAXPARAMSIZE> parentValues, const int currentIndex, const int maxIndex) {
    set<array<unsigned int, MAXPARAMSIZE>> newSet;
    for (auto precon = (&UnaryActionLiterals)->begin(); precon != (&UnaryActionLiterals)->end(); precon++) {
        if (precon->args.at(0) == currentIndex) {
            if (state->unaryFacts.contains(precon->predicateIndex)) {
                for (auto fact : state->unaryFacts.at(precon->predicateIndex)) {
                    if (!Contains(parentValues, fact)) {
                        array<unsigned int, MAXPARAMSIZE> newValues = parentValues;
                        newValues.at(currentIndex) = fact;
                        if (IsBinaryLegal(state, &newValues, currentIndex + 1)) {
                            if (currentIndex + 1 >= maxIndex) {
                                newSet.emplace(newValues);
                            }
                            else {
                                set<array<unsigned int, MAXPARAMSIZE>> returnSet = GetCandidates(state, newValues, currentIndex + 1, maxIndex);
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

bool ActionGenerator2::Contains(array<unsigned int, MAXPARAMSIZE> values, unsigned int value) {
    for (auto parent : values) {
        if (value == parent)
            return true;
    }
    return false;
}

bool ActionGenerator2::IsBinaryLegal(const PDDLState* state, array<unsigned int, MAXPARAMSIZE>* set, const int currentMax) {
    for (auto precon = (&BinaryActionLiterals)->begin(); precon != (&BinaryActionLiterals)->end(); precon++) {
        int arg1 = precon->args.at(0);
        int arg2 = precon->args.at(1);
        if (arg1 < currentMax && arg2 < currentMax) {
            if (!state->binaryFacts.at(precon->predicateIndex).contains(make_pair(set->at(arg1), set->at(arg2)))) {
                return false;
            }
        }
    }
    return true;
}