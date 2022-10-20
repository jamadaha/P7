#include "ActionGenerator.hpp"

std::vector<PDDLActionInstance> ActionGenerator::GenerateActions(const PDDLState *state) {
    std::vector<PDDLActionInstance> legalActions;
    for (int i = 0; i < domain->actions.size(); i++) {
        std::vector<PDDLActionInstance> tempActions = GenerateLegal(&(domain->actions[i]), state);
        for (int t = 0; t < tempActions.size(); t++)
            legalActions.push_back(tempActions[t]);
    }
    return legalActions;
}

std::vector<PDDLActionInstance> ActionGenerator::GenerateLegal(const PDDLAction *action, const PDDLState *state) {
    std::vector<PDDLActionInstance> legalActions;

    std::unordered_set<const PDDLLiteral*> unaryLiterals[action->parameters.size()];

    // Find what preconditions are applicible to what arguments
    // Should likely be static somehow
    for (int i = 0; i < action->preconditions.size(); i++)
        for (int a = 0; a < action->preconditions[i].args.size(); a++) {
            if (action->preconditions[i].args.size() == 1)
                unaryLiterals[action->preconditions[i].args[a]].emplace(&(action->preconditions[i]));
        }
            

    // Object which fulfill the unary literals of the action preconditions
    std::vector<std::unordered_set<unsigned int>> candidateObjects;
    candidateObjects.reserve(action->parameters.size());
    for (int i = 0; i < action->parameters.size(); i++)
        candidateObjects.push_back(GetCandidateObjects(&(unaryLiterals[i]), state));
    
    
    // if some parameter doesn't have any candidate object, the action is not possible
    for (int i = 0; i < action->parameters.size(); i++)
        if (candidateObjects[i].size() == 0)
            return legalActions;

    std::vector<std::unordered_set<unsigned int>::iterator> iteration;
    iteration.reserve(candidateObjects.size());
    for (int i = 0; i < candidateObjects.size(); i++)
        iteration.push_back(candidateObjects[i].begin());


    // Iterate over each pairing of candidate objects
    // Then remove those that do not match non-unary preconditions
    // Those that match all are added as a legal action
    do {
        std::vector<unsigned int> objects;
        objects.reserve(action->parameters.size());
        for (int i = 0; i < iteration.size(); i++)
            objects.push_back((*iteration[i]));

        if (IsLegal(&action->preconditions, state, &objects))
            legalActions.push_back(PDDLActionInstance(action, objects));

    } while (Iterate(&iteration, &candidateObjects));
 
    return legalActions;
}

std::unordered_set<unsigned int> ActionGenerator::GetCandidateObjects(std::unordered_set<const PDDLLiteral*> *literals, const PDDLState *state) {
    std::unordered_set<unsigned int> candidateObjects;

    // Firs is setting candidate objects to the smallest set from some predicate
    int sPredicateIndex = -1;
    unsigned int smallestCount = 99999;
    for (auto iter = literals->begin(); iter != literals->end(); iter++) {
        if (state->unaryFacts.at((*iter)->predicateIndex).size() < smallestCount) {
            sPredicateIndex = (*iter)->predicateIndex;
            smallestCount = state->unaryFacts.at((*iter)->predicateIndex).size();
        }
    }

    // If some unary action applies to this, set it, else set to all objects
    if (sPredicateIndex != -1)
        candidateObjects = state->unaryFacts.at(sPredicateIndex);
    else {
        candidateObjects.reserve(problem->objects.size());
        for (int i = 0; i < problem->objects.size(); i++)
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

bool ActionGenerator::IsLegal(const std::vector<PDDLLiteral> *literals, const PDDLState *state, std::vector<unsigned int> *objects) {
    for (int i = 0; i < literals->size(); i++) {
        auto literal = &(literals->at(i));
        if (literal->args.size() < 2)
            continue;
        if (literal->predicateIndex == 0) {
            bool areEqual = (objects->at(0) == objects->at(1));
            if (areEqual != literal->value)
                return false;
        } else {
            bool found = false;
            for (int f = 0; f < state->multiFacts.at(literal->predicateIndex).size(); f++) {
                bool valid = true;
                auto multiFact = &(state->multiFacts.at(literal->predicateIndex).at(f).fact);
                for (int a = 0; a < multiFact->size(); a++) {
                    if (objects->at(a) != multiFact->at(a)) {
                        valid = false;
                        break;
                    }
                }

                if (valid) {
                    found = true;
                    break;
                }                
            }
            if (found != literals->at(i).   value)
                return false;
        }
    }
    return true;
}

bool ActionGenerator::Iterate(std::vector<std::unordered_set<unsigned int>::iterator> *iteration, std::vector<std::unordered_set<unsigned int>> *candidateObjects) {
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
