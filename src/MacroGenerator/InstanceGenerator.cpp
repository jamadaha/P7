#include "InstanceGenerator.hh"

PDDLInstance InstanceGenerator::GenerateInstance(const PDDLDomain *domain, const PDDLProblem *problem, const std::vector<Macro> *macros) {
    std::vector<PDDLPredicate> predicates = domain->predicates;
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
            predicates.push_back(PDDLPredicate(predicate, 1));
        }
    }

    std::vector<PDDLAction> actions; actions.reserve(domain->actions.size() + macros->size());
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

        std::vector<PDDLLiteral> preconditions = GenerateLiterals(&macro->groundedAction.preconditions, &groundedToIndex);
        AppendObjectPreconditions(&preconditions, predicateMap, parameters);
        std::vector<PDDLLiteral> effects = GenerateLiterals(&macro->groundedAction.effects, &groundedToIndex);
        actions.push_back(PDDLAction(macro->name, parameters, preconditions, effects));
    }

    PDDLDomain *newDomain = new PDDLDomain(domain->name, domain->requirements, predicates, predicateMap, actions);


    PDDLProblem *newProblem = new PDDLProblem(problem->name, 
    newDomain, problem->objects, problem->objectMap, PDDLState(unaryFacts, problem->initState.binaryFacts), problem->goalState);

    return PDDLInstance(newDomain, newProblem);
}

std::vector<PDDLLiteral> InstanceGenerator::GenerateLiterals(const std::unordered_map<GroundedLiteral, bool> *groundedLiterals, 
std::unordered_map<unsigned int, unsigned int> *groundedToIndex) {
    std::vector<PDDLLiteral> literals; literals.reserve(groundedLiterals->size());
    for (auto iter = groundedLiterals->begin(); iter != groundedLiterals->end(); iter++) {
        std::vector<unsigned int> args; args.reserve((*iter).first.objects.size());
        for (int i = 0; i < (*iter).first.objects.size(); i++)
            args.push_back(groundedToIndex->at((*iter).first.objects.at(i)));
        literals.push_back(PDDLLiteral((*iter).first.predicate, args, (*iter).second));
    }
    return literals;
}

void InstanceGenerator::AppendObjectPreconditions(std::vector<PDDLLiteral> *literals, 
const std::unordered_map<std::string, unsigned int> predicateMap,
const std::vector<std::string> parameters) {
    for (unsigned int i = 0; i < parameters.size(); i++) {
        std::string object = parameters.at(i).substr(1);
        std::string predicate = "is-" + object;
        literals->push_back(PDDLLiteral(predicateMap.at(predicate), std::vector<unsigned int>{ i }, true));
    }
}