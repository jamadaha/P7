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

    std::vector<std::unordered_set<const PDDLLiteral*>> applicableLiterals;
    applicableLiterals.reserve(action->parameters.size());

    // Init vector for each parameter
    for (int i = 0; i < action->parameters.size(); i++)
        applicableLiterals.push_back(std::unordered_set<const PDDLLiteral*>());

    // Find what preconditions are applicible to what arguments
    // Should likely be static somehow
    for (int i = 0; i < action->preconditions.size(); i++)
        for (int a = 0; a < action->preconditions[i].args.size(); a++)
            applicableLiterals.at(action->preconditions[i].args[a]).emplace(&(action->preconditions[i]));

    // Object which fulfill the unary literals of the action preconditions
    std::vector<std::unordered_set<unsigned int>> candidateObjects;
    candidateObjects.reserve(action->parameters.size());
    for (int i = 0; i < action->parameters.size(); i++)
        candidateObjects.push_back(GetCandidateObjects(applicableLiterals[i], state));
    
    
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
                //legalActions.push_back(PDDLActionInstance(action, objects));
    } while (Iterate(&iteration, &candidateObjects));
 
    return legalActions;
}

std::unordered_set<unsigned int> ActionGenerator::GetCandidateObjects(std::unordered_set<const PDDLLiteral*> literals, const PDDLState *state) {
    std::unordered_set<unsigned int> candidateObjects;
    for (int i = 0; i < problem->objects.size(); i++)
        candidateObjects.emplace(i);

    // Check what objects match all literals
    for (auto literal = literals.begin(); literal != literals.end(); literal++) {
        // Ignore if non unary literal
        if ((*literal)->args.size() != 1)
            continue;
        
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
        if (literals->at(i).args.size() < 2)
            continue;
        auto literal = literals->at(i);
        if (literal.predicateIndex == 0) {
            bool areEqual = (objects->at(0) == objects->at(1));
            if (areEqual != literal.value)
                return false;
        } else {
            bool found = false;
            for (int f = 0; f < state->multiFacts.at(literal.predicateIndex).size(); f++) {
                bool valid = true;
                for (int a = 0; a < state->multiFacts.at(literal.predicateIndex).at(f).fact.size(); a++)
                    if (objects->at(a) != state->multiFacts.at(literal.predicateIndex).at(f).fact[a])
                        valid = false;

                if (valid) {
                    found = true;
                    break;
                }                
            }
            if (found != literal.value)
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
