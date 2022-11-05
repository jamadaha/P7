#include "MacroGenerator.hh"

using namespace std;

Macro MacroGenerator::GenerateMacro(const MacroCandidate* candidate) {
    vector<GroundedAction> groundedActions = GroundActions(&candidate->Entanglements.at(0));
    GroundedAction combinedAction = CombineActions(&groundedActions);
    return Macro(combinedAction, CloneOriginalPath(&candidate->Entanglements.at(0)));
}

vector<PDDLActionInstance> MacroGenerator::CloneOriginalPath(const vector<PDDLActionInstance*> *actions) {
    vector<PDDLActionInstance> newPath;
    for (int i = 0; i < actions->size(); i++)
        newPath.push_back(PDDLActionInstance(actions->at(i)->action, actions->at(i)->objects));
    return newPath;
}

// Duplicate code inside, remove at some point
vector<GroundedAction> MacroGenerator::GroundActions(const vector<PDDLActionInstance*> *actions) {
    vector<GroundedAction> groundedActions; groundedActions.reserve(actions->size());

    for (int i = 0; i < actions->size(); i++) {
        const PDDLActionInstance *action = actions->at(i);
        string name = action->action->name + to_string(groundedActionsCount++);
        // Get parameters
        unordered_set<unsigned int> parameters;
        for (int t = 0; t < action->objects.size(); t++) parameters.emplace(action->objects.at(t));
        // Get preconditions
        const vector<PDDLLiteral> *actionPrecon = &action->action->preconditions;
        unordered_map<GroundedLiteral, bool> preconditions; preconditions.reserve(actionPrecon->size());
        for (int t = 0; t < actionPrecon->size(); t++) {
            const PDDLLiteral *lit = &actionPrecon->at(t);
            vector<unsigned int> args; args.reserve(lit->args.size());
            for (int q = 0; q < lit->args.size(); q++) args.push_back(action->objects.at(lit->args.at(q)));
            preconditions.emplace(GroundedLiteral(lit->predicateIndex, args), lit->value);
        }
        // Get effects
        const vector<PDDLLiteral> *actionEffs = &action->action->effects;
        unordered_map<GroundedLiteral, bool> effects; effects.reserve(actionEffs->size());
        for (int t = 0; t < actionEffs->size(); t++) {
            const PDDLLiteral *lit = &actionEffs->at(t);
            vector<unsigned int> args; args.reserve(lit->args.size());
            for (int q = 0; q < lit->args.size(); q++) args.push_back(action->objects.at(lit->args.at(q)));
            effects.emplace(GroundedLiteral(lit->predicateIndex, args), lit->value);
        }
        groundedActions.push_back(GroundedAction(action->action->name, parameters, preconditions, effects));
    }
    return groundedActions;
}

GroundedAction MacroGenerator::CombineActions(const vector<GroundedAction> *actions) {
    // Initialize to first element in actions
    string name = to_string(macroCount++);
    unordered_map<GroundedLiteral, bool> preconditions;
    unordered_map<GroundedLiteral, bool> effects;

    // Combine through vector with accumalitive combination
    for (int i = 0; i < actions->size(); i++) {
        name += "-" + actions->at(i).name;
        preconditions = CombinePreconditions(preconditions, actions->at(i).preconditions, effects);
        effects = CombineEffects(effects, actions->at(i).effects);
    }
    
    return GroundedAction(name, GenerateParameters(preconditions, effects), preconditions, effects);
}

// Pre_1 union (Pre_2 - Eff_1)
unordered_map<GroundedLiteral, bool> MacroGenerator::CombinePreconditions( 
unordered_map<GroundedLiteral, bool> priorPrecon, 
unordered_map<GroundedLiteral, bool> latterPrecon,
unordered_map<GroundedLiteral, bool> priorEffs) {
    unordered_map<GroundedLiteral, bool> preconditions = priorPrecon;

    for (auto iter : latterPrecon) {
        // If part of effect do not add to preconditions
        // Assumes that the precondition and effect cannot have different values
        if (priorEffs.contains(iter.first)) continue;
        if (preconditions.contains(iter.first)) continue; // maybe
        if (iter.first.predicate == 0) continue;
        if (domain != nullptr && domain->staticPredicates.contains(iter.first.predicate)) continue;
        preconditions.emplace(iter.first, iter.second);
    }

    return preconditions;
}
// Eff_2 union Eff_1 ?
unordered_map<GroundedLiteral, bool> MacroGenerator::CombineEffects(
unordered_map<GroundedLiteral, bool> priorEffects, 
unordered_map<GroundedLiteral, bool> latterEffects) {
    unordered_map<GroundedLiteral, bool> effects = priorEffects;

    for (auto iter : latterEffects) {
        effects[iter.first] = iter.second;
    }

    return effects;
}

unordered_set<unsigned int> MacroGenerator::GenerateParameters(
unordered_map<GroundedLiteral, bool> preconditions, 
unordered_map<GroundedLiteral, bool> effects) {
    unordered_set<unsigned int> parameters;

    for (auto map : preconditions)
        for (auto iter = map.first.objects.begin(); iter != map.first.objects.end(); iter++)
            parameters.emplace((*iter));
    for (auto map : effects)
        for (auto iter = map.first.objects.begin(); iter != map.first.objects.end(); iter++)
            parameters.emplace((*iter));

    return parameters;
}
