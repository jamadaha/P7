#include "Instantiator.hh"

using namespace std;
using namespace Macros;

PDDLInstance Instantiator::GenerateInstance(const PDDLDomain *domain, const PDDLProblem *problem, const vector<Macro> *macros) {
    vector<PDDLAction> actions = domain->actions;
    vector<PDDLPredicate> predicates = domain->predicates;
    unordered_map<string, unsigned int> predicateMap = domain->predicateMap;
    unordered_map<unsigned int, unordered_set<unsigned int>> unaryFacts = problem->initState.unaryFacts;

    GenerateUnaryFacts(macros, problem, &predicateMap, &unaryFacts, &predicates);
    GenerateMacroActions(macros, problem, &predicateMap, &actions);

    PDDLDomain *newDomain = new PDDLDomain(domain->name, domain->requirements, predicates, predicateMap, actions);

    PDDLProblem *newProblem = new PDDLProblem(
        problem->name, 
        newDomain, 
        problem->objects, 
        problem->objectMap, 
        PDDLState(unaryFacts, problem->initState.binaryFacts), 
        problem->goalState);

    return PDDLInstance(newDomain, newProblem);
}

void Instantiator::GenerateUnaryFacts(
        const vector<Macro>* macros,
        const PDDLProblem* problem,
        unordered_map<string, unsigned int>* predicateMap,
        unordered_map<unsigned int, unordered_set<unsigned int>>* unaryFacts,
        vector<PDDLPredicate>* predicates)
{
    for (int i = 0; i < macros->size(); i++) {
        const Macro* macro = &macros->at(i);
        for (auto iter = macro->groundedAction.parameters.begin(); iter != macro->groundedAction.parameters.end(); iter++) {
            string predicate = "IS-" + problem->objects.at(*iter);
            if (predicateMap->contains(predicate))
                continue;

            unaryFacts->emplace(predicates->size(), unordered_set<unsigned int>());
            unaryFacts->at(predicates->size()).emplace(*iter);

            predicateMap->emplace(predicate, predicates->size());
            predicates->push_back(PDDLPredicate(predicate, 1));
        }
    }
}

void Instantiator::GenerateMacroActions(
    const vector<Macro>* macros,
    const PDDLProblem* problem,
    const unordered_map<string, unsigned int>* predicateMap,
    vector<PDDLAction>* actions) 
{
    for (int i = 0; i < macros->size(); i++) {
        const Macro* macro = &macros->at(i);
        const unordered_set<unsigned int>* macroParameters = &macro->groundedAction.parameters;
        unordered_map<unsigned int, unsigned int> groundedToIndex; 
        groundedToIndex.reserve(macroParameters->size());
        for (auto iter = macroParameters->begin(); iter != macroParameters->end(); iter++)
            groundedToIndex.emplace((*iter), groundedToIndex.size());

        vector<string> parameters; 
        parameters.reserve(macroParameters->size());
        for (auto iter = macroParameters->begin(); iter != macroParameters->end(); iter++) {
            string parameter = "?" + problem->objects.at(*iter);
            parameters.push_back(parameter);
        }

        vector<PDDLLiteral> preconditions = GenerateLiterals(&macro->groundedAction.preconditions, &groundedToIndex);
        AppendObjectPreconditions(&preconditions, predicateMap, &parameters);
        vector<PDDLLiteral> effects = GenerateLiterals(&macro->groundedAction.effects, &groundedToIndex);
        actions->push_back(PDDLAction(macro->name, parameters, preconditions, effects));
    }
}

vector<PDDLLiteral> Instantiator::GenerateLiterals(
        const unordered_map<GroundedLiteral, bool> *groundedLiterals, 
        unordered_map<unsigned int, unsigned int> *groundedToIndex) 
{
    vector<PDDLLiteral> literals; 
    literals.reserve(groundedLiterals->size());
    for (auto iter = groundedLiterals->begin(); iter != groundedLiterals->end(); iter++) {
        vector<unsigned int> args; 
        args.reserve((*iter).first.objects.size());
        for (int i = 0; i < (*iter).first.objects.size(); i++)
            args.push_back(groundedToIndex->at((*iter).first.objects.at(i)));
        literals.push_back(PDDLLiteral((*iter).first.predicate, args, (*iter).second));
    }
    return literals;
}

void Instantiator::AppendObjectPreconditions(
        vector<PDDLLiteral> *literals, 
        const unordered_map<string, unsigned int>* predicateMap,
        const vector<string>* parameters) 
{
    for (unsigned int i = 0; i < parameters->size(); i++) {
        string object = parameters->at(i).substr(1);
        string predicate = "IS-" + object;
        literals->push_back(PDDLLiteral(predicateMap->at(predicate), vector<unsigned int>{ i }, true));
    }
}