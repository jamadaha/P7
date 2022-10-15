#include "ActionGenerator.hpp"

std::vector<PDDLActionInstance> ActionGenerator::GenerateActions(PDDLState *state) {
    std::vector<PDDLActionInstance> legalActions;
    for (int i = 0; i < domain->actions.size(); i++) {
        std::vector<PDDLActionInstance> tempActions = GenerateLegal(&(domain->actions[i]), state);
        for (int t = 0; t < tempActions.size(); t++)
            legalActions.push_back(tempActions[t]);
    }
    return legalActions;
}

std::vector<PDDLActionInstance> ActionGenerator::GenerateLegal(const PDDLAction *action, PDDLState *state) {
    std::vector<PDDLActionInstance> legalActions;

    std::vector<std::unordered_set<const PDDLLiteral*>> applicableLiterals;
    applicableLiterals.reserve(action->parameterCount);

    // Init vector for each parameter
    for (int i = 0; i < action->parameterCount; i++)
        applicableLiterals.push_back(std::unordered_set<const PDDLLiteral*>());

    // Find what preconditions are applicible to what arguments
    // Should likely be static somehow
    for (int i = 0; i < action->preconditions.size(); i++)
        for (int a = 0; a < action->preconditions[i].args.size(); a++)
            applicableLiterals.at(action->preconditions[i].args[a]).emplace(&(action->preconditions[i]));

    // Object which fulfill the unary literals of the action preconditions
    std::vector<std::unordered_set<unsigned int>> candidateObjects;
    candidateObjects.reserve(action->parameterCount);
    for (int i = 0; i < action->parameterCount; i++)
        candidateObjects.push_back(GetCandidateObjects(applicableLiterals[i], state));
    
    /*
    // if some parameter doesn't have any candidate object, the action is not possible
    for (int i = 0; i < parameterCount; i++)
        if (candidateObjects[i].size() == 0)
            return legalActions;

    std::vector<int> indexes(parameterCount, 0);
    do {
        std::vector<std::string> objects;
        for (int i = 0; i < parameterCount; i++) 
            objects.push_back(candidateObjects[i][indexes[i]]);
        // test whether any multi literals do not match these objects
        bool legalAction = true;
        for (int i = 0; i < parameterCount; i++) {
            for (int l = 0; l < multiLiterals[i].size(); l++) {
                if (!state->IsMultiLiteralTrue(&action, multiLiterals[i][l], objects)) {
                    legalAction = false;
                    break;
                }  
            }
            if (!legalAction)
                break;
        }
        if (legalAction)
                legalActions.push_back(PDDLActionInstance(action, objects));
        
    } while (Increment(&indexes, candidateObjects)); */
 
    return legalActions;
}

std::unordered_set<unsigned int> ActionGenerator::GetCandidateObjects(std::unordered_set<const PDDLLiteral*> literals, PDDLState *state) {
    std::unordered_set<unsigned int> candidateObjects;

    bool first = true;

    // Check what objects match all literals
    for (auto literal = literals.begin(); literal != literals.end(); literal++) {
        // Ignore if non unary literal
        if ((*literal)->args.size() != 1)
            continue;
        
        if (first) {
            // Set candidateobjects equal to those objects that fulfill first literal
            candidateObjects = state->unaryFacts.at((*literal)->predicateIndex);
            first = false;
        } else {
            // Find intersection of candidateobjects and the new literal
            auto newObjectRef = &(state->unaryFacts.at((*literal)->predicateIndex));
            // Returns true, i.e. object should be deleted, if newobject ref does not contain it
            const auto NewObjectNegContains = [&](auto const& x) { return !newObjectRef->contains(x); };
            // Remove those which are not contained in both
            std::erase_if(candidateObjects, NewObjectNegContains);
        }
    }

    return candidateObjects;
}

/*
std::vector<PDDLLiteral> ActionGenerator::GetPreconditions(PDDLAction *action, PDDLArg *param) {
    std::vector<PDDLLiteral> preconditions;
     for (int p = 0; p < action->preconditions.size(); p++)
        for (int i = 0; i < action->preconditions[p].predicate->args.size(); i++)
            if (action->preconditions[p].args[i] == param) {
                preconditions.push_back(action->preconditions[p]);
                break;
            }   
    return preconditions;
}

std::vector<std::string> ActionGenerator::GetCandidateObjects(PDDLAction* action, PDDLState *state, std::vector<PDDLLiteral> preconditions) {
    std::vector<std::string> candidateObjects;
    for (int o = 0; o < state->objects->size(); o++) {
        bool validObject = true;
        for (int p = 0; p < preconditions.size(); p++) {
            if (!state->IsUnaryLiteralTrue(action, preconditions[p], state->objects[0][o])) {
                validObject = false;
                break;
            }
        }  
        if (validObject)
            candidateObjects.push_back(state->objects[0][o]);
    } 
    return candidateObjects;    
}

void ActionGenerator::SplitLiterals(std::vector<PDDLLiteral> literals, std::vector<PDDLLiteral> *unaryLiterals, std::vector<PDDLLiteral> *multiLiterals) {
     for (int i = 0; i < literals.size(); i++)
        if (literals[i].predicate.args.size() > 1)
            (*multiLiterals).push_back(literals[i]);
        else
            (*unaryLiterals).push_back(literals[i]); 
}

bool ActionGenerator::Increment(std::vector<int> *indexes, std::vector<std::string> objects[]) {
    int incrementIndex = -1;
    for (int i = 0; i < indexes->size(); i++) {
        if ((*indexes)[i] + 1 < objects[i].size()) {
            (*indexes)[i]++;
            incrementIndex = i;
            break;
        }
    }
    for (int i = 0; i < incrementIndex; i++)
        (*indexes)[i] = 0;
    return (incrementIndex != -1);
}
 */