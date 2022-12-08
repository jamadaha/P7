#include "State.hh"
#include "Instance.hh"

using namespace std;
using namespace PDDL;

DoActionChanges State::DoAction(const ActionInstance *action) {
    DoActionChanges changes = DoActionChanges();
    auto objects = &action->objects;
    for (int i = 0; i < action->action->negEffects.size(); i++) {
        auto effect = action->action->negEffects.at(i);
        DoEffect(effect, objects, &changes);
    }
    for (int i = 0; i < action->action->posEffects.size(); i++) {
        auto effect = action->action->posEffects.at(i);
        DoEffect(effect, objects, &changes);
    }

    return changes;
}

void State::DoEffect(const Literal* lit, const std::vector<unsigned int> *objects, DoActionChanges *changes) {
    if (lit->args.size() == 1)
        DoUnaryEffect(lit, objects, changes);
    else
        DoBinaryEffect(lit, objects, changes);
}

void State::DoUnaryEffect(const Literal* lit, const std::vector<unsigned int> *objects, DoActionChanges *changes) {
    const auto object = objects->at(lit->args.at(0));
    
    if (lit->value) {
        if (!unaryFacts.at(lit->predicateIndex).contains(object)) {
            unaryFacts.at(lit->predicateIndex).emplace(object);
            changes->AddChange(lit->predicateIndex, object, lit->value); 
        }
    } else {
        if (unaryFacts.at(lit->predicateIndex).contains(object)) {
            unaryFacts.at(lit->predicateIndex).erase(object);
            changes->AddChange(lit->predicateIndex, object, lit->value); 
        }
    }
}

void State::DoBinaryEffect(const Literal* lit, const std::vector<unsigned int> *objects, DoActionChanges *changes) {
    auto pair = make_pair(objects->at(lit->args.at(0)), objects->at(lit->args.at(1)));
    
    if (lit->value) {
        if (!binaryFacts.at(lit->predicateIndex).contains(pair)) {
            binaryFacts.at(lit->predicateIndex).emplace(pair);
            changes->AddChange(lit->predicateIndex, pair, lit->value); 
        }
    } else {
        if (binaryFacts.at(lit->predicateIndex).contains(pair)) {
            binaryFacts.at(lit->predicateIndex).erase(pair);
            changes->AddChange(lit->predicateIndex, pair, lit->value); 
        }
    }
}

void State::UndoAction(const DoActionChanges *changes) {
    auto unaryChanges = &changes->unaryChanges;
    auto binaryChanges = &changes->binaryChanges;

    for (auto uChangeIter = unaryChanges->begin(); uChangeIter != unaryChanges->end(); uChangeIter++) {
        auto predicate = (*uChangeIter).first;
        auto changes = &(*uChangeIter).second;
        for (auto changeIter = changes->begin(); changeIter != changes->end(); changeIter++) {
            auto change = &*changeIter;
            if (change->second)
                unaryFacts.at(predicate).erase(change->first);
            else
                unaryFacts.at(predicate).emplace(change->first);
        }
    }

    for (auto bChangeIter = binaryChanges->begin(); bChangeIter != binaryChanges->end(); bChangeIter++) {
        auto predicate = (*bChangeIter).first;
        auto changes = &(*bChangeIter).second;
        for (auto changeIter = changes->begin(); changeIter != changes->end(); changeIter++) {
            auto change = &*changeIter;
            if (change->second)
                binaryFacts.at(predicate).erase(change->first);
            else
                binaryFacts.at(predicate).emplace(change->first);
        }
    }
}

string State::ToString(const Instance* instance)
{
    string temp = "State ";
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
