#include "InstanceGenerator.hh"

PDDL::Instance InstanceGenerator::GenerateInstance(const PDDL::Domain *domain, const PDDL::Problem *problem, const std::vector<Macro> *macros) {
    std::vector<PDDL::Predicate> predicates = domain->predicates;
    std::unordered_map<std::string, unsigned int> predicateMap = domain->predicateMap;
    std::unordered_map<unsigned int, std::unordered_set<unsigned int>> unaryFacts = problem->initState.unaryFacts;

    for (int i = 0; i < macros->size(); i++) {
        const Macro *macro = &macros->at(i);
        for (auto iter = macro->groundedAction.parameters.begin(); iter != macro->groundedAction.parameters.end(); iter++) {
            std::string predicate = "is-" + problem->objects.at(*iter);
            if (predicateMap.contains(predicate)) continue;
            unaryFacts.emplace(predicates.size(), std::unordered_set<unsigned int>());
            unaryFacts.at(predicates.size()).emplace(*iter);
            predicateMap.emplace(predicate, predicates.size());
            predicates.push_back(PDDL::Predicate(predicate, 1));
        }
    }

    std::vector<PDDL::Action> actions; actions.reserve(domain->actions.size() + macros->size());
    for (int i = 0; i < domain->actions.size(); i++)
        actions.push_back(domain->actions.at(i));
    for (int i = 0; i < macros->size(); i++) {
        const Macro *macro = &macros->at(i);
        const std::unordered_set<unsigned int> *macroParameters = &macro->groundedAction.parameters;
        std::unordered_map<unsigned int, unsigned int> groundedToIndex; groundedToIndex.reserve(macroParameters->size());
        for (auto iter = macroParameters->begin(); iter != macroParameters->end(); iter++)
            groundedToIndex.emplace((*iter), groundedToIndex.size());
        
        std::vector<std::string> parameters; parameters.reserve(macroParameters->size());
        for (auto iter = macroParameters->begin(); iter != macroParameters->end(); iter++) {
            std::string parameter = "?" + problem->objects.at(*iter);
            parameters.push_back(parameter);
        }

        std::vector<PDDL::Literal> preconditions = GenerateLiterals(&macro->groundedAction.preconditions, &groundedToIndex);
        AppendObjectPreconditions(&preconditions, predicateMap, parameters);
        std::vector<PDDL::Literal> effects = GenerateLiterals(&macro->groundedAction.effects, &groundedToIndex);
        actions.push_back(PDDL::Action(macro->name, parameters, preconditions, effects));
    }

    PDDL::Domain *newDomain = new PDDL::Domain(domain->name, domain->requirements, predicates, predicateMap, actions);


    PDDL::Problem *newProblem = new PDDL::Problem(problem->name, 
    newDomain, problem->objects, problem->objectMap, PDDL::State(unaryFacts, problem->initState.binaryFacts), problem->goalState);

    return PDDL::Instance(newDomain, newProblem);
}

std::vector<PDDL::Literal> InstanceGenerator::GenerateLiterals(const std::unordered_map<GroundedLiteral, bool> *groundedLiterals, 
std::unordered_map<unsigned int, unsigned int> *groundedToIndex) {
    std::vector<PDDL::Literal> literals; literals.reserve(groundedLiterals->size());
    for (auto iter = groundedLiterals->begin(); iter != groundedLiterals->end(); iter++) {
        std::vector<unsigned int> args; args.reserve((*iter).first.objects.size());
        for (int i = 0; i < (*iter).first.objects.size(); i++)
            args.push_back(groundedToIndex->at((*iter).first.objects.at(i)));
        literals.push_back(PDDL::Literal((*iter).first.predicate, args, (*iter).second));
    }
    return literals;
}

void InstanceGenerator::AppendObjectPreconditions(std::vector<PDDL::Literal> *literals, 
const std::unordered_map<std::string, unsigned int> predicateMap,
const std::vector<std::string> parameters) {
    for (unsigned int i = 0; i < parameters.size(); i++) {
        std::string object = parameters.at(i).substr(1);
        std::string predicate = "is-" + object;
        literals->push_back(PDDL::Literal(predicateMap.at(predicate), std::vector<unsigned int>{ i }, true));
    }
}