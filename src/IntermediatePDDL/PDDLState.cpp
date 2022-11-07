#include "PDDLState.hh"

#include "PDDLInstance.hh"

std::size_t PDDLState::GetHash() {
    return std::hash<PDDLState>{}(*this);
}

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
        } else if (effect.args.size() == 2) {
            // Handle binary effect
            if (effect.value)
                binaryFacts.at(effect.predicateIndex).emplace(std::make_pair(action->objects.at(effect.args.at(0)), action->objects.at(effect.args.at(1))));
            else
                binaryFacts.at(effect.predicateIndex).erase(std::make_pair(action->objects.at(effect.args.at(0)), action->objects.at(effect.args.at(1))));
        } else {
            // Handle multi effect
            if (effect.value)
                multiFacts.at(effect.predicateIndex).emplace(MultiFact(action->objects));
            else
                multiFacts.at(effect.predicateIndex).erase(MultiFact(action->objects));
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
        } else if (effect.args.size() == 2) {
            // Handle binary effect
            if (!effect.value)
                binaryFacts.at(effect.predicateIndex).emplace(std::make_pair(action->objects.at(effect.args.at(0)), action->objects.at(effect.args.at(1))));
            else
                binaryFacts.at(effect.predicateIndex).erase(std::make_pair(action->objects.at(effect.args.at(0)), action->objects.at(effect.args.at(1))));
        } else {
            // Handle multi effect
            if (!effect.value)
                multiFacts.at(effect.predicateIndex).emplace(MultiFact(action->objects));
            else
                multiFacts.at(effect.predicateIndex).erase(MultiFact(action->objects));
        }
    }
}

std::string PDDLState::ToString(const PDDLInstance* instance)
{
    std::string temp = "State ";
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

    for (auto &multiFact : multiFacts) {
        for (auto &facts : multiFact.second) {
            temp += "(";
            temp += instance->domain->predicates[multiFact.first].name;
            for (auto fact : facts.fact) {
                
                temp += " " + instance->problem->objects[fact];
               
            }
            temp += ")";
        }
    }

    temp += "\n";
    return temp;
};
