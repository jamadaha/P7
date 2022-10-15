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
    PDDLDomain() : name("Not Set") {};
    PDDLDomain(std::string name, std::vector<std::string> requirements, std::vector<PDDLPredicate> predicates, 
    std::unordered_map<std::string, unsigned int> predicateMap, std::vector<PDDLAction> actions) :
    name(name), requirements(requirements), predicates(predicates), 
    predicateMap(predicateMap), actions(actions) {}; 
};

#endif
