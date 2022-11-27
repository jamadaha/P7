#ifndef PDDL_DOMAIN_HH
#define PDDL_DOMAIN_HH

#include <vector>
#include <string>
#include <unordered_map>
#include <map>

#include "Predicate.hh"
#include "Action.hh"
#include "../Helpers/AlgorithmHelper.hh"

namespace PDDL {
    class Domain {
        const std::string name;
        const std::vector<std::string> requirements;
        const std::vector<Predicate> predicates;
        // Goes from predicate name to index in "predicates"
        // e.g. "ROOM" => 0, "IsBall" => 1,...
        const std::unordered_map<std::string, unsigned int> predicateMap;
        const std::vector<Action> actions;
        // Set of predicates which are in no effects
        const std::unordered_set<unsigned int> staticPredicates;
        // Set of predicates which are in atleast one effect
        const std::unordered_set<unsigned int> nonStaticPredicates;
        Domain() : name("Not Set") {};
        Domain(std::vector<Action> actions) : name("Only actions"), actions(actions) {};
        Domain(std::string name, std::vector<std::string> requirements, std::vector<Predicate> predicates,
            std::unordered_map<std::string, unsigned int> predicateMap, std::vector<Action> actions) :
            name(name), requirements(requirements), predicates(predicates),
            predicateMap(predicateMap), actions(actions), staticPredicates(GetStaticPredicates()), nonStaticPredicates(GetNonStaticPredicates()) {};

    private:
        std::unordered_set<unsigned int> GetStaticPredicates() {
            std::unordered_set<unsigned int> candidateIndexes; candidateIndexes.reserve(predicates.size());
            for (int i = 1; i < predicates.size(); i++)
                candidateIndexes.emplace(i);
            for (auto iter = actions.begin(); iter != actions.end(); iter++) {
                for (auto litIter = (*iter).effects.begin(); litIter != (*iter).effects.end(); litIter++) {
                    if (candidateIndexes.contains((*litIter).predicateIndex))
                        candidateIndexes.erase((*litIter).predicateIndex);
                }
            }
            return candidateIndexes;
        }

        std::unordered_set<unsigned int> GetNonStaticPredicates() {
            std::unordered_set<unsigned int> tempPredicates; tempPredicates.reserve(predicates.size() - staticPredicates.size());
            for (unsigned int i = 1; i < predicates.size(); i++)
                if (!staticPredicates.contains(i))
                    tempPredicates.emplace(i);
            return tempPredicates;
        }
    };
}

#endif
