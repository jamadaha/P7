#include "ActionGenerator.hpp"

using namespace std;

vector<PDDLActionInstance*> ActionGenerator::GenerateActions(const PDDLState *state) {
    vector<PDDLActionInstance*> legalActions;
    const int domainLength = domain->actions.size();
    for (int i = 0; i < domainLength; i++) {
        vector<PDDLActionInstance*> tempActions = GenerateLegal(&(domain->actions[i]), state);
        const int actionsLength = tempActions.size();
        for (int t = 0; t < actionsLength; t++)
            legalActions.push_back(tempActions[t]);
    }
    return legalActions;
}

vector<PDDLActionInstance*> ActionGenerator::GenerateLegal(const PDDLAction *action, const PDDLState *state) {
    vector<PDDLActionInstance*> legalActions;

    unordered_set<const PDDLLiteral*> unaryLiterals[action->parameters.size()];

    // Find what preconditions are applicible to what arguments
    // Should likely be static somehow
    const int preconditionLength = action->preconditions.size();
    for (int i = 0; i < preconditionLength; i++) {
        const int preconditionArgsLength = action->preconditions[i].args.size();
        for (int a = 0; a < preconditionArgsLength; a++) {
            if (action->preconditions[i].args.size() == 1)
                unaryLiterals[action->preconditions[i].args[a]].emplace(&(action->preconditions[i]));
        }
    }

    // Object which fulfill the unary literals of the action preconditions
    vector<unordered_set<unsigned int>> candidateObjects;
    candidateObjects.reserve(action->parameters.size());
    const int parameterLength = action->parameters.size();
    for (int i = 0; i < parameterLength; i++) {
        auto candididateObjects = GetCandidateObjects(&(unaryLiterals[i]), state);
        // if some parameter doesn't have any candidate object, the action is not possible
        if (candididateObjects.size() == 0)
            return legalActions;
        candidateObjects.push_back(candididateObjects);
    }
    
    // if some parameter doesn't have any candidate object, the action is not possible
    //for (int i = 0; i < parameterLength; i++)
    //    if (candidateObjects[i].size() == 0)
    //        return legalActions;

    vector<unordered_set<unsigned int>::iterator> iteration;
    const int candidateObjectsLength = candidateObjects.size();
    iteration.reserve(candidateObjectsLength);
    for (int i = 0; i < candidateObjectsLength; i++)
        iteration.push_back(candidateObjects[i].begin());

    // Iterate over each pairing of candidate objects
    // Then remove those that do not match non-unary preconditions
    // Those that match all are added as a legal action
    const int iterationSize = iteration.size();
    do {
        vector<unsigned int> objects;
        objects.reserve(parameterLength);

        for (int i = 0; i < iterationSize; i++)
            objects.push_back((*iteration[i]));

        if (IsLegal(&action->preconditions, state, &objects))
            legalActions.push_back(new PDDLActionInstance(action, objects));

    } while (Iterate(&iteration, &candidateObjects));
 
    return legalActions;
}

unordered_set<unsigned int> ActionGenerator::GetCandidateObjects(unordered_set<const PDDLLiteral*> *literals, const PDDLState *state) {
    unordered_set<unsigned int> candidateObjects;

    // Find first positive literal, and set candidate objects to those applicable
    for (auto iter = literals->begin(); iter != literals->end(); iter++) {
        if ((*iter)->args.size() > 1)
            continue;
        if ((*iter)->value == true) {
            candidateObjects = state->unaryFacts.at((*iter)->predicateIndex);
            break;
        }
    }

    if (candidateObjects.size() == 0) {
        const int problemObjectsSize = problem->objects.size();
        candidateObjects.reserve(problemObjectsSize);
        for (int i = 0; i < problemObjectsSize; i++)
            candidateObjects.emplace(i);
    }

    // Check what objects match all literals
    for (auto literal = literals->begin(); literal != literals->end(); literal++) {
        // Find intersection of candidateobjects and the new literal
        auto newObjectRef = &(state->unaryFacts.at((*literal)->predicateIndex));
        // Returns true, i.e. object should be deleted, depending on the literal state
        const auto NewObjectNegContains = [&](auto const& x) { return newObjectRef->contains(x) != (*literal)->value; };
        // Remove those which are(n't) contained in both depending on literal value
        std::erase_if(candidateObjects, NewObjectNegContains);
    }

    return candidateObjects;
}

bool ActionGenerator::IsLegal(const vector<PDDLLiteral> *literals, const PDDLState *state, vector<unsigned int> *objects) {
    const int literalsLength = literals->size();
    for (int i = 0; i < literalsLength; i++) {
        const PDDLLiteral* literal = &(literals->at(i));
        if (literal->args.size() < 2)
            continue;
        if (literal->predicateIndex == 0) {
            if (objects->size() > 1) {
                bool areEqual = (objects->at(0) == objects->at(1));
                if (areEqual != literal->value)
                    return false;
            }
        }
        else
        {
            const auto multiFact = &state->multiFacts.at(literal->predicateIndex);

            bool found = false;
            const int multiFactLength = multiFact->size();
            for (int f = 0; f < multifactsLenght; f++) {
                bool valid = true;
                auto multiFactFact = &multiFact->at(f).fact;
                auto multiFactFactLength = multiFactFact->size();
                for (int a = 0; a < multiFactFactLength; a++) {
                    if (objects->at(a) != multiFactFact->at(a)) {
                        valid = false;
                        break;
                    }
                }

                if (valid) {
                    found = true;
                    break;
                }
            }
            if (found != literal->value)
                return false;
        }
        
    }
    return true;
}

bool ActionGenerator::Iterate(vector<unordered_set<unsigned int>::iterator> *iteration, vector<unordered_set<unsigned int>> *candidateObjects) {
    int incrementIndex = -1;
    for (int i = 0; i < iteration->size(); i++) {
        auto next = std::next((*iteration)[i], 1);
        if (next != (*candidateObjects)[i].end()) {
            (*iteration)[i]++;
            incrementIndex = i;
            break;
        }
    }
    for (int i = 0; i < incrementIndex; i++)
        (*iteration)[i] = (*candidateObjects)[i].begin();
    return (incrementIndex != -1);
}
