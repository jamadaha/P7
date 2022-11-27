#include "MacroGenerator.hh"

using namespace std;

Macro MacroGenerator::GenerateMacro(vector<PDDLActionInstance> *actions) {
    vector<GroundedAction> groundedActions = GroundActions(actions);
    GroundedAction combinedAction = CombineActions(&groundedActions);
    return Macro(combinedAction, *actions);
}

vector<GroundedAction> MacroGenerator::GroundActions(vector<PDDLActionInstance> *actions) {
    vector<GroundedAction> groundedActions; 
    groundedActions.reserve(actions->size());

    for (int i = 0; i < actions->size(); i++)
        groundedActions.push_back(GroundAction(&actions->at(i)));

    return groundedActions;
}

GroundedAction MacroGenerator::GroundAction(PDDLActionInstance* action) {
    // Get parameters
    unordered_set<unsigned int> parameters;
    for (int t = 0; t < action->objects.size(); t++)
        parameters.emplace(action->objects.at(t));

    // Get preconditions
    const vector<PDDLLiteral>* preconditions = &action->action->preconditions;
    unordered_map<GroundedLiteral, bool> groundedPreconditions;
    groundedPreconditions.reserve(preconditions->size());
    for (auto lit = preconditions->begin(); lit != preconditions->end(); lit++)
        groundedPreconditions.emplace(GroundedLiteral(lit->predicateIndex, GetGroundedArguments(action, lit->args)), lit->value);

    // Get effects
    const vector<PDDLLiteral>* effects = &action->action->effects;
    unordered_map<GroundedLiteral, bool> groundedEffects;
    groundedEffects.reserve(effects->size());
    for (auto lit = effects->begin(); lit != effects->end(); lit++)
        groundedEffects.emplace(GroundedLiteral(lit->predicateIndex, GetGroundedArguments(action, lit->args)), lit->value);

    return GroundedAction(action->action->name, parameters, groundedPreconditions, groundedEffects);
}

vector<unsigned int> MacroGenerator::GetGroundedArguments(PDDLActionInstance* action, vector<unsigned int> args) {
    vector<unsigned int> returnArgs;
    args.reserve(2);
    for (int q = 0; q < args.size(); q++)
        returnArgs.push_back(action->objects.at(args.at(q)));
    return returnArgs;
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
        unordered_map<GroundedLiteral, bool> priorEffs) 
{
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

// Eff_2 union Eff_1
unordered_map<GroundedLiteral, bool> MacroGenerator::CombineEffects(
        unordered_map<GroundedLiteral, bool> priorEffects, 
        unordered_map<GroundedLiteral, bool> latterEffects) 
{
    unordered_map<GroundedLiteral, bool> effects = priorEffects;

    for (auto iter : latterEffects) {
        effects[iter.first] = iter.second;
    }

    return effects;
}

unordered_set<unsigned int> MacroGenerator::GenerateParameters(
        unordered_map<GroundedLiteral, bool> preconditions, 
        unordered_map<GroundedLiteral, bool> effects) 
{
    unordered_set<unsigned int> parameters;

    for (auto map : preconditions)
        for (auto iter : map.first.objects)
            parameters.emplace(iter);
    for (auto map : effects)
        for (auto iter : map.first.objects)
            parameters.emplace(iter);

    return parameters;
}
