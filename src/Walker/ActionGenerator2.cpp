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
    for (auto predicate = (&action->preconditions)->begin(); predicate != (&action->preconditions)->end(); predicate++) {
        if (predicate->args.size() == 1)
            UnaryActionLiterals.push_back(*predicate);
        else if (predicate->args.size() == 2)
            BinaryActionLiterals.push_back(*predicate);
    }
    UnaryActionLiteralsPtr = &UnaryActionLiterals;
    BinaryActionLiteralsPtr = &BinaryActionLiterals;
}

void ActionGenerator2::GetCandidates(set<array<unsigned int, MAXPARAMSIZE>>* candidates, const PDDLState* state, const array<unsigned int, MAXPARAMSIZE> parentValues, const int currentIndex, const int maxIndex) {
    vector<unsigned int> objectCandidates;
    objectCandidates.reserve(TEMPOBJSIZE);
    for (auto precon = UnaryActionLiteralsPtr->begin(); precon != UnaryActionLiteralsPtr->end(); precon++) {
        if (precon->args.at(0) == currentIndex) {
            if (objectCandidates.size() == 0) {
                for (auto fact : state->unaryFacts.at(precon->predicateIndex))
                    objectCandidates.push_back(fact);
            }
            else {
                for (int i = 0; i < objectCandidates.size(); i++) {
                    if (!state->unaryFacts.at(precon->predicateIndex).contains(objectCandidates.at(i))) {
                        objectCandidates.erase(objectCandidates.begin() + i);
                        i--;
                    }
                }
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

bool ActionGenerator2::IsBinaryLegal(const PDDLState* state, const array<unsigned int, MAXPARAMSIZE>* set, const int currentMax) {
    for (auto precon = BinaryActionLiteralsPtr->begin(); precon != BinaryActionLiteralsPtr->end(); precon++) {
        int arg1 = precon->args.at(0);
        int arg2 = precon->args.at(1);
        if (arg1 <= currentMax && arg2 <= currentMax) {
            auto value = make_pair(set->at(arg1), set->at(arg2));
            if (!state->ContainsFact(precon->predicateIndex, value))
                return false;
        }
    }
    return true;
}
