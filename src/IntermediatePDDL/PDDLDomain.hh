#ifndef PDDL_DOMAIN_HH
#define PDDL_DOMAIN_HH

#include <vector>
#include <string>
#include <unordered_map>
#include <map>

#include "PDDLPredicate.hh"
#include "PDDLAction.hh"
#include "../PDDLParser/domain.hh"

struct PDDLDomain {
    const std::string name;
    const std::vector<std::string> requirements;
    const std::vector<PDDLPredicate> predicates;
    // Goes from predicate name to index in "predicates"
    // e.g. "ROOM" => 0, "IsBall" => 1,...
    const std::unordered_map<std::string, unsigned int> predicateMap;
    const std::vector<PDDLAction> actions;
    // For each predicate, which actions have them in effect (I.e. doing an action in this, changes facts related to the given predicate)
    const std::vector<std::unordered_set<const PDDLAction*>> predicateActions;
    // Set of predicates which are in no effects
    const std::unordered_set<unsigned int> staticPredicates;
    PDDLDomain() : name("Not Set") {};
    PDDLDomain(std::vector<PDDLAction> actions) : name("Only actions"), actions(actions) {};
    PDDLDomain(std::string name, std::vector<std::string> requirements, std::vector<PDDLPredicate> predicates, 
    std::unordered_map<std::string, unsigned int> predicateMap, std::vector<PDDLAction> actions) :
    name(name), 
    requirements(requirements), 
    predicates(predicates), 
    predicateMap(predicateMap), 
    actions(actions), 
    predicateActions(GetPredicateActions()),
    staticPredicates(GetStaticPredicates()) {}; 

private:
    std::vector<std::unordered_set<const PDDLAction*>> GetPredicateActions() {
        std::vector<std::unordered_set<const PDDLAction*>> tempPredicateActions; tempPredicateActions.reserve(predicates.size());
        for (int i = 0; i < predicates.size(); i++)
            tempPredicateActions.push_back({});

        for (int i = 0; i < actions.size(); i++) {
            auto action = &actions.at(i);
            for (auto iter = action->effects.begin(); iter != action->effects.end(); iter++) {
                tempPredicateActions.at((*iter).predicateIndex).emplace(action);
            }
        }
        return tempPredicateActions;
    }

    std::unordered_set<unsigned int> GetStaticPredicates() {
        std::unordered_set<unsigned int> candidateIndexes; candidateIndexes.reserve(predicates.size());
        for (int i = 0; i < predicateActions.size(); i++)
            if (predicateActions.at(i).size() == 0)
                candidateIndexes.emplace(i);
        return candidateIndexes;
    }
};

#endif
