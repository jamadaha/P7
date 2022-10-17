#include "PDDLState.hh"

PDDLState *PDDLState::Do(const PDDLActionInstance* actionInstance) {
    auto unaryFacts = this->unaryFacts;
    auto multiFacts = this->multiFacts;

    for (int i = 0; i < actionInstance->action->effects.size(); i++) {
        auto effect = actionInstance->action->effects.at(i);
        if (effect.args.size() == 1) {
            // Handle unary effect
            if (effect.value)
                unaryFacts.at(effect.predicateIndex).emplace(actionInstance->objects.at(effect.args.at(0)));
            else
                unaryFacts.at(effect.predicateIndex).erase(actionInstance->objects.at(effect.args.at(0)));
        } else {
            // Handle multi effect
            int index = -1;
            for (int f = 0; f < multiFacts.at(effect.predicateIndex).size(); f++) {
                bool equal = true;
                for (int e = 0; e < effect.args.size(); e++) {
                    if (multiFacts.at(effect.predicateIndex).at(f).fact.at(e) !=
                        actionInstance->objects.at(effect.args.at(e))) {
                            equal = false;
                            break;
                        }
                }
                if (equal) {
                    index = f;
                    break;
                }
            }
            if (effect.value) {
                if (index == -1) {
                    std::vector<unsigned int> factArgs;
                    factArgs.reserve(effect.args.size());
                    for (int i = 0; i < effect.args.size(); i++)
                        factArgs.push_back(actionInstance->objects.at(effect.args.at(i)));
                    multiFacts.at(effect.predicateIndex).push_back(MultiFact(factArgs));
                }
            } else {
                if (index != -1) {
                    auto fact = multiFacts.at(effect.predicateIndex);
                    fact.erase(fact.begin());
                }
            }
        }
    }

    return new PDDLState(unaryFacts, multiFacts);
}
