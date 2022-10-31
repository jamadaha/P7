#include "MacroGenerator.hh"

Macro MacroGenerator::GenerateMacro(const std::vector<PDDLActionInstance*> *actions) {
    std::vector<GroundedAction> groundedActions = GroundActions(actions);
    GroundedAction combinedAction = CombineActions(&groundedActions);
    return Macro(combinedAction, CloneOriginalPath(actions));
}


std::vector<PDDLActionInstance> MacroGenerator::CloneOriginalPath(const std::vector<PDDLActionInstance*> *actions) {
    std::vector<PDDLActionInstance> newPath;
    for (int i = 0; i < actions->size(); i++)
        newPath.push_back(PDDLActionInstance(actions->at(i)->action, actions->at(i)->objects));
    return newPath;
}

// Duplicate code inside, remove at some point
std::vector<GroundedAction> MacroGenerator::GroundActions(const std::vector<PDDLActionInstance*> *actions) {
    std::vector<GroundedAction> groundedActions; groundedActions.reserve(actions->size());

    for (int i = 0; i < actions->size(); i++) {
        const PDDLActionInstance *action = actions->at(i);
        std::string name = action->action->name + std::to_string(groundedActionsCount++);
        // Get parameters
        std::unordered_set<unsigned int> parameters;
        for (int t = 0; t < action->objects.size(); t++) parameters.emplace(action->objects.at(t));
        // Get preconditions
        const std::vector<PDDLLiteral> *actionPrecon = &action->action->preconditions;
        std::unordered_map<GroundedLiteral, bool> preconditions; preconditions.reserve(actionPrecon->size());
        for (int t = 0; t < actionPrecon->size(); t++) {
            const PDDLLiteral *lit = &actionPrecon->at(t);
            std::vector<unsigned int> args; args.reserve(lit->args.size());
            for (int q = 0; q < lit->args.size(); q++) args.push_back(action->objects.at(lit->args.at(q)));
            preconditions.emplace(GroundedLiteral(lit->predicateIndex, args), lit->value);
        }
        // Get effects
        const std::vector<PDDLLiteral> *actionEffs = &action->action->effects;
        std::unordered_map<GroundedLiteral, bool> effects; effects.reserve(actionEffs->size());
        for (int t = 0; t < actionEffs->size(); t++) {
            const PDDLLiteral *lit = &actionEffs->at(t);
            std::vector<unsigned int> args; args.reserve(lit->args.size());
            for (int q = 0; q < lit->args.size(); q++) args.push_back(action->objects.at(lit->args.at(q)));
            effects.emplace(GroundedLiteral(lit->predicateIndex, args), lit->value);
        }
        groundedActions.push_back(GroundedAction(action->action->name, parameters, preconditions, effects));
    }
    return groundedActions;
}

GroundedAction MacroGenerator::CombineActions(const std::vector<GroundedAction> *actions) {
    // Initialize to first element in actions
    std::string name = std::to_string(macroCount++) + "-" + actions->at(0).name;
    std::unordered_map<GroundedLiteral, bool> preconditions = actions->at(0).preconditions;
    std::unordered_map<GroundedLiteral, bool> effects = actions->at(0).effects;

    // Combine through vector with accumalitive combination
    for (int i = 1; i < actions->size(); i++) {
        name += "-" + actions->at(i).name;
        preconditions = CombinePreconditions(preconditions, actions->at(i).preconditions, effects);
        effects = CombineEffects(effects, actions->at(i).effects);
    }
    
    return GroundedAction(name, GenerateParameters(preconditions, effects), preconditions, effects);
}

// Pre_1 union (Pre_2 - Eff_1)
std::unordered_map<GroundedLiteral, bool> MacroGenerator::CombinePreconditions( 
std::unordered_map<GroundedLiteral, bool> priorPrecon, 
std::unordered_map<GroundedLiteral, bool> latterPrecon,
std::unordered_map<GroundedLiteral, bool> priorEffs) {
    std::unordered_map<GroundedLiteral, bool> preconditions = priorPrecon;

    for (auto iter : latterPrecon) {
        // If part of effect do not add to preconditions
        // Assumes that the precondition and effect cannot have different values
        if (priorEffs.contains(iter.first)) continue;
        if (preconditions.contains(iter.first)) continue; // maybe
        preconditions.emplace(iter.first, iter.second);
    }

    return preconditions;
}
// Eff_2 union Eff_1 ?
std::unordered_map<GroundedLiteral, bool> MacroGenerator::CombineEffects(
std::unordered_map<GroundedLiteral, bool> priorEffects, 
std::unordered_map<GroundedLiteral, bool> latterEffects) {
    std::unordered_map<GroundedLiteral, bool> effects = priorEffects;

    for (auto iter : latterEffects) {
        effects[iter.first] = iter.second;
    }

    return effects;
}

std::unordered_set<unsigned int> MacroGenerator::GenerateParameters(
std::unordered_map<GroundedLiteral, bool> preconditions, 
std::unordered_map<GroundedLiteral, bool> effects) {
    std::unordered_set<unsigned int> parameters;

    for (auto map : preconditions)
        for (auto iter = map.first.objects.begin(); iter != map.first.objects.end(); iter++)
            parameters.emplace((*iter));
    for (auto map : effects)
        for (auto iter = map.first.objects.begin(); iter != map.first.objects.end(); iter++)
            parameters.emplace((*iter));

    return parameters;
}
