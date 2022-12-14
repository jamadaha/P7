#include "ActionGenerator2.hpp"

using namespace std;

vector<PDDL::ActionInstance> ActionGenerator2::GenerateActions(const PDDL::State* state) {
    vector<PDDL::ActionInstance> legalActions;
    for (auto iter = actions->begin(); iter != actions->end(); iter++) {
        vector<PDDL::ActionInstance> tempActions = GenerateActions(&(*iter), state);
        copy(tempActions.begin(), tempActions.end(), back_inserter(legalActions));
    }
    
    branchingFactors.push_back(legalActions.size());

    totalActions += legalActions.size();
    return legalActions;
}

vector<PDDL::ActionInstance> ActionGenerator2::GenerateActions(const PDDL::Action* action, const PDDL::State* state) {
    vector<PDDL::ActionInstance> legalActions;

    UnaryActionLiteralsPtr = &action->unaryPreconditions;
    BinaryActionLiteralsPtr = &action->binaryPreconditions;

    array<unsigned int, MAXPARAMSIZE> parentValues;
    parentValues.fill(-1);

    set<array<unsigned int, MAXPARAMSIZE>> candidates;
    GetCandidates(&candidates, state, parentValues, 0, action->parameters.size());

    for (auto candidate : candidates)
        legalActions.push_back(PDDL::ActionInstance(action, vector<unsigned int>(candidate.begin(), candidate.begin() + action->parameters.size())));

    return legalActions;
}

// Recursively look through every parameter option, and check if they are valid
// If they are valid, add them to the candidate set
void ActionGenerator2::GetCandidates(set<array<unsigned int, MAXPARAMSIZE>>* candidates, const PDDL::State* state, const array<unsigned int, MAXPARAMSIZE> parentValues, const int currentIndex, const int maxIndex) {
    vector<unsigned int> objectCandidates;
    objectCandidates.reserve(TEMPOBJSIZE);
    bool wasAny = false;
    // Check all unary literals that match the parameter index
    for (auto precon = UnaryActionLiteralsPtr->begin(); precon != UnaryActionLiteralsPtr->end(); precon++) {
        if (precon->args.at(0) == currentIndex) {
            wasAny = true;
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
            // If the candidates are now empty, the current object configuration is now invalid.
            if (objectCandidates.size() == 0)
                break;
        }
    }

    // If there where no precondition for this parameter, assume that all objects are valid
    if (!wasAny)
        for (auto object : objects)
            objectCandidates.push_back(object);

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

// Check if all binary predicates are valid with the current parameters.
// If a predicate refers to a parameter that is outside of currentMax, ignore it.
bool ActionGenerator2::IsBinaryLegal(const PDDL::State* state, const array<unsigned int, MAXPARAMSIZE>* set, const int currentMax) {
    if (currentMax < 1)
        return true;

    for (auto precon = BinaryActionLiteralsPtr->begin(); precon != BinaryActionLiteralsPtr->end(); precon++) {
        int arg1 = precon->args.at(0);
        int arg2 = precon->args.at(1);
        if (arg1 <= currentMax && arg2 <= currentMax && (arg1 == currentMax || arg2 == currentMax)) {
            auto value = make_pair(set->at(arg1), set->at(arg2));
            if (state->ContainsFact(precon->predicateIndex, value) != precon->value)
                return false;
        }
    }

    return true;
}
