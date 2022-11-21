#include "PDDLState.hh"

#include "PDDLInstance.hh"

void PDDLState::DoAction(const PDDLActionInstance *action) {
    int actionEffectLength = action->action->effects.size();
    for (int i = 0; i < actionEffectLength; i++) {
        PDDLLiteral effect = action->action->effects.at(i);
        if (effect.args.size() == 1) {
            // Handle unary effect
            if (effect.value)
                unaryFacts.at(effect.predicateIndex).emplace(action->objects.at(effect.args.at(0)));
            else
                unaryFacts.at(effect.predicateIndex).erase(action->objects.at(effect.args.at(0)));
        } else {
            // Handle binary effect
            if (effect.value)
                binaryFacts.at(effect.predicateIndex).emplace(std::make_pair(action->objects.at(effect.args.at(0)), action->objects.at(effect.args.at(1))));
            else
                binaryFacts.at(effect.predicateIndex).erase(std::make_pair(action->objects.at(effect.args.at(0)), action->objects.at(effect.args.at(1))));
        }
    }
}

void PDDLState::UndoAction(const PDDLActionInstance *action) {
    int actionEffectLength = action->action->effects.size();
    for (int i = 0; i < actionEffectLength; i++) {
        PDDLLiteral effect = action->action->effects.at(i);
        if (effect.args.size() == 1) {
            // Handle unary effect
            if (!effect.value)
                unaryFacts.at(effect.predicateIndex).emplace(action->objects.at(effect.args.at(0)));
            else
                unaryFacts.at(effect.predicateIndex).erase(action->objects.at(effect.args.at(0)));
        } else {
            // Handle binary effect
            if (!effect.value)
                binaryFacts.at(effect.predicateIndex).emplace(std::make_pair(action->objects.at(effect.args.at(0)), action->objects.at(effect.args.at(1))));
            else
                binaryFacts.at(effect.predicateIndex).erase(std::make_pair(action->objects.at(effect.args.at(0)), action->objects.at(effect.args.at(1))));
        }
    }
}

std::string PDDLState::ToString(const PDDLInstance* instance)
{
    std::string temp = "State ";
    temp += "\n";
    for (auto &unaryFact : unaryFacts)
    {
        if (unaryFact.second.size() > 0) {
            temp += "(";
            temp += instance->domain->predicates[unaryFact.first].name;

            for (auto objectindex : unaryFact.second) {
                temp += " " + instance->problem->objects[objectindex];
            }
            temp += ")";
        }
    }

    for (auto &binaryFact : binaryFacts)
    {
        temp += "\n";
        if (binaryFact.second.size() > 0) {
            temp += "(";
            temp += instance->domain->predicates[binaryFact.first].name;

            for (auto objectindex : binaryFact.second) {
                temp += " (" + instance->problem->objects[objectindex.first] + " " + instance->problem->objects[objectindex.second] + ")";
            }
            temp += ")";
        }
    }

    return temp;
};
