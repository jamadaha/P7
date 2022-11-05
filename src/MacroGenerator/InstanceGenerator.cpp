#include "InstanceGenerator.hh"

PDDLInstance InstanceGenerator::GenerateInstance(const PDDLDomain *domain, const PDDLProblem *problem, const std::vector<Macro> *macros) {
    std::vector<PDDLPredicate> predicates = domain->predicates;
    std::unordered_map<std::string, unsigned int> predicateMap = domain->predicateMap;
    std::unordered_map<unsigned int, std::unordered_set<unsigned int>> unaryFacts = problem->initState.unaryFacts;

    for (int i = 0; i < macros->size(); i++) {
        const Macro *macro = &macros->at(i);
        for (auto iter = macro->groundedAction.parameters.begin(); iter != macro->groundedAction.parameters.end(); iter++) {
            std::string predicate = "IS-";
            for (auto innerItter = iter->begin(); innerItter != iter->end(); innerItter++) {
                predicate += problem->objects.at(*innerItter) + "-";
            }
            predicate = predicate.substr(0, predicate.size() - 1);
            if (predicateMap.contains(predicate)) continue;

            for (auto innerItter = iter->begin(); innerItter != iter->end(); innerItter++) {
                unaryFacts.emplace(predicates.size(), std::unordered_set<unsigned int>());
                unaryFacts.at(predicates.size()).emplace(*innerItter);
            }
            predicateMap.emplace(predicate, predicates.size());
            predicates.push_back(PDDLPredicate(predicate, 1));
        }
    }

    std::vector<PDDLAction> actions; actions.reserve(domain->actions.size() + macros->size());
    for (int i = 0; i < domain->actions.size(); i++)
        actions.push_back(domain->actions.at(i));
    for (int i = 0; i < macros->size(); i++) {
        int paramsCounter = 0;
        const Macro *macro = &macros->at(i);
        std::vector<std::string> parameters;

        std::unordered_map<unsigned int, unsigned int> groundedToIndex;
        for (auto iter = macro->groundedAction.parameters.begin(); iter != macro->groundedAction.parameters.end(); iter++) {
            for (auto iter2 = iter->begin(); iter2 != iter->end(); iter2++)
                groundedToIndex.emplace((*iter2), groundedToIndex.size());

            std::string parameter = "?";
            for (auto iter2 = iter->begin(); iter2 != iter->end(); iter2++) {
                parameter += problem->objects.at(*iter2) + "-";
            }
            parameter = parameter.substr(0, parameter.size() - 1);
            parameters.push_back(parameter);
        }

        std::vector<PDDLLiteral> preconditions = GenerateLiterals(&macro->groundedAction.preconditions, &groundedToIndex);
        AppendObjectPreconditions(&preconditions, predicateMap, parameters);
        std::vector<PDDLLiteral> effects = GenerateLiterals(&macro->groundedAction.effects, &groundedToIndex);
        actions.push_back(PDDLAction(macro->name, parameters, preconditions, effects));
    }

    PDDLDomain *newDomain = new PDDLDomain(domain->name, domain->requirements, predicates, predicateMap, actions);


    PDDLProblem *newProblem = new PDDLProblem(problem->name, 
        newDomain, problem->objects, problem->objectMap, PDDLState(unaryFacts, problem->initState.binaryFacts, problem->initState.multiFacts), problem->goalState);

    return PDDLInstance(newDomain, newProblem);
}

std::vector<PDDLLiteral> InstanceGenerator::GenerateLiterals(const std::unordered_map<GroundedLiteral, bool> *groundedLiterals, 
std::unordered_map<unsigned int, unsigned int> *groundedToIndex) {
    std::vector<PDDLLiteral> literals; literals.reserve(groundedLiterals->size());
    for (auto iter = groundedLiterals->begin(); iter != groundedLiterals->end(); iter++) {
        std::vector<unsigned int> args; 
        args.reserve((*iter).first.objects.at(0).size());
        for (int i = 0; i < (*iter).first.objects.at(0).size(); i++)
            args.push_back(groundedToIndex->at((*iter).first.objects.at(0).at(i)));
        literals.push_back(PDDLLiteral((*iter).first.predicate, args, (*iter).second));
    }
    return literals;
}

void InstanceGenerator::AppendObjectPreconditions(std::vector<PDDLLiteral> *literals, 
const std::unordered_map<std::string, unsigned int> predicateMap,
const std::vector<std::string> parameters) {
    for (unsigned int i = 0; i < parameters.size(); i++) {
        std::string object = parameters.at(i).substr(1);
        std::string predicate = "IS-" + object;
        literals->push_back(PDDLLiteral(predicateMap.at(predicate), std::vector<unsigned int>{ i }, true));
    }
}