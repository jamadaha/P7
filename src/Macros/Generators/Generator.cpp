#include "Generator.hh"

using namespace std;
using namespace Macros;

Macro Generator::GenerateMacro(vector<PDDLActionInstance> *actions) {
    vector<GroundedAction> groundedActions = GroundActions(actions);
    GroundedAction combinedAction = CombineActions(&groundedActions);
    return Macro(combinedAction, *actions);
}

vector<GroundedAction> Generator::GroundActions(vector<PDDLActionInstance> *actions) {
    vector<GroundedAction> groundedActions; 
    groundedActions.reserve(actions->size());

    for (int i = 0; i < actions->size(); i++)
        groundedActions.push_back(GroundAction(&actions->at(i)));

    return groundedActions;
}

GroundedAction Generator::GroundAction(PDDLActionInstance* action) {
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

vector<unsigned int> Generator::GetGroundedArguments(PDDLActionInstance* action, vector<unsigned int> args) {
    vector<unsigned int> returnArgs;
    returnArgs.reserve(2);
    for (int q = 0; q < args.size(); q++)
        returnArgs.push_back(action->objects.at(args.at(q)));
    return returnArgs;
}

GroundedAction Generator::CombineActions(const vector<GroundedAction> *actions) {
    // Initialize to first element in actions
    string name = to_string(macroCount++);
    unordered_map<GroundedLiteral, bool> preconditions;
    unordered_map<GroundedLiteral, bool> effects;

    // Combine through vector with accumalitive combination
    for (int i = 0; i < actions->size(); i++) {
        name += "-" + actions->at(i).name;
        CombinePreconditions(&preconditions, actions->at(i).preconditions, &effects);
        CombineEffects(&effects, actions->at(i).effects);
    }
    
    return GroundedAction(name, GenerateParameters(&preconditions, &effects), preconditions, effects);
}

// Pre_1 union (Pre_2 - Eff_1)
void Generator::CombinePreconditions(
        unordered_map<GroundedLiteral, bool>* priorPrecon, 
        unordered_map<GroundedLiteral, bool> latterPrecon,
        unordered_map<GroundedLiteral, bool>* priorEffs) 
{
    for (auto iter : latterPrecon) {
        // If part of effect do not add to preconditions
        // Assumes that the precondition and effect cannot have different values
        if (priorEffs->contains(iter.first)) continue;
        if (priorPrecon->contains(iter.first)) continue; // maybe
        if (iter.first.predicate == 0) continue;
        if (domain != nullptr && domain->staticPredicates.contains(iter.first.predicate)) continue;
        priorPrecon->emplace(iter.first, iter.second);
    }
}

// Eff_2 union Eff_1
void Generator::CombineEffects(
        unordered_map<GroundedLiteral, bool>* priorEffects, 
        unordered_map<GroundedLiteral, bool> latterEffects) 
{
    for (auto iter : latterEffects) {
        if (priorEffects->contains(iter.first))
            priorEffects->at(iter.first) = iter.second;
        else
            priorEffects->emplace(iter.first, iter.second);
    }
}

unordered_set<unsigned int> Generator::GenerateParameters(
        unordered_map<GroundedLiteral, bool>* preconditions, 
        unordered_map<GroundedLiteral, bool>* effects) 
{
    unordered_set<unsigned int> parameters;

    for (auto map = preconditions->begin(); map != preconditions->end(); map++)
        for (auto iter : map->first.objects)
            parameters.emplace(iter);
    for (auto map = effects->begin(); map != effects->end(); map++)
        for (auto iter : map->first.objects)
            parameters.emplace(iter);

    return parameters;
}
