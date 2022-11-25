#include "PartialActionGenerator.hh"

#include "../../Helpers/AlgorithmHelper.hh"

std::vector<PartialAction> PartialActionGenerator::ExpandState(const PDDLState *state) {
    std::vector<PartialAction> partialActions;

    // Generate actions for unary facts
    for (auto iter = state->unaryFacts.begin(); iter != state->unaryFacts.end(); iter++)
        for (auto objectIter = (*iter).second.begin(); objectIter != (*iter).second.end(); objectIter++)
            AlgorithmHelper::InsertAll<PartialAction>(partialActions, ExpandUnary(std::make_pair((*iter).first, (*objectIter))));  


    // Generate actions for binary facts
    for (auto iter = state->binaryFacts.begin(); iter != state->binaryFacts.end(); iter++)
        for (auto objectIter = (*iter).second.begin(); objectIter != (*iter).second.end(); objectIter++)
            AlgorithmHelper::InsertAll<PartialAction>(partialActions, ExpandBinary(std::make_pair((*iter).first, (*objectIter))));    

    return partialActions;
}

std::vector<PartialAction> PartialActionGenerator::ExpandUnary(std::pair<unsigned int, unsigned int> predicateObject) {
    std::vector<PartialAction> partialActions;

    for (int i = 0; i < actions->size(); i++) {
        const PDDLAction *action = &actions->at(i);

        for (int t = 0; t < action->effects.size(); t++) {
            const PDDLLiteral *effect = &action->effects.at(t);

            if (predicateObject.first == effect->predicateIndex && effect->value) {
                partialActions.push_back(CreateFromUnary(action, effect->args.at(0), predicateObject.second));
                break;
            }
        }
    }

    return partialActions;
}

std::vector<PartialAction> PartialActionGenerator::ExpandBinary(std::pair<unsigned int, std::pair<unsigned int, unsigned int>> predicateObjects) {
    std::vector<PartialAction> partialActions;

    for (int i = 0; i < actions->size(); i++) {
        const PDDLAction *action = &actions->at(i);

        for (int t = 0; t < action->effects.size(); t++) {
            const PDDLLiteral *effect = &action->effects.at(t);

            if (predicateObjects.first == effect->predicateIndex && effect->value) {
                partialActions.push_back(CreateFromBinay(action, std::make_pair(effect->args.at(0), effect->args.at(1)), predicateObjects.second));
                break;
            }
        }
    }

    return partialActions;
}

PartialAction PartialActionGenerator::CreateFromUnary(const PDDLAction *action, const unsigned int index, const unsigned int object) {
    std::vector<unsigned int*> tempObjects;

    for (int i = 0; i < action->parameters.size(); i++) {
        if (index == i)
            tempObjects.push_back(new unsigned int(object));
        else
            tempObjects.push_back(nullptr);
    }

    return PartialAction(action, tempObjects);
}

PartialAction PartialActionGenerator::CreateFromBinay(const PDDLAction *action, const std::pair<unsigned int, unsigned int> indexes, const std::pair<unsigned int, unsigned int> objects) {
    std::vector<unsigned int*> tempObjects;

    for (int i = 0; i < action->parameters.size(); i++) {
        if (indexes.first == i)
            tempObjects.push_back(new unsigned int(objects.first));
        else if (indexes.second == i)
            tempObjects.push_back(new unsigned int(objects.second));
        else
            tempObjects.push_back(nullptr);
    }

    return PartialAction(action, tempObjects);
}

void PartialActionGenerator::FillPartialAction(const PDDLInstance *instance, PartialAction *partialAction) {
    for (unsigned int i = 0; i < partialAction->parameters.size(); i++) {
        if (partialAction->parameters.at(i) == nullptr)
            partialAction->parameters.at(i) = new unsigned int(GetParameterCandidate(instance, partialAction->action, &i));
    }
}

PDDLActionInstance PartialActionGenerator::ConvertPartialAction(const PDDLInstance *instance, const PartialAction *partialAction) {
    std::vector<unsigned int> objects;
    for (unsigned int i = 0; i < partialAction->parameters.size(); i++) {
        if (partialAction->parameters.at(i) != nullptr)
            objects.push_back(*partialAction->parameters.at(i));
        else
            objects.push_back(GetParameterCandidate(instance, partialAction->action, &i));
    }
    return PDDLActionInstance(partialAction->action, objects);
}


unsigned int PartialActionGenerator::GetParameterCandidate(const PDDLInstance *instance, const PDDLAction *action, const unsigned int *paramIndex) {
    const PDDLLiteral *staticLiteral = nullptr;
    for (auto iter = action->applicableUnaryLiterals.at(*paramIndex).begin(); iter != action->applicableUnaryLiterals.at(*paramIndex).end(); iter++)
        if (instance->domain->staticPredicates.contains((*iter)->predicateIndex)) {
            staticLiteral = *iter;
            break;
        }
    if (staticLiteral == nullptr) {
        // do something better at some point
        return rand() % instance->problem->objects.size();
    } else {
        auto predicateIndex = staticLiteral->predicateIndex;
        auto state = &instance->problem->initState;
        if (staticLiteral->args.size() == 1) {
            return *std::next(state->unaryFacts.at(predicateIndex).begin(), rand() % state->unaryFacts.at(predicateIndex).size());
        } else
            throw std::logic_error("Not implemented");
    }
}
