#include "Instantiator.hh"

using namespace std;
using namespace Macros;
using namespace PDDL;

Instance Instantiator::GenerateInstance(const Domain *domain, const Problem *problem, const vector<Macro> *macros) {
    vector<Action> actions = domain->actions;
    vector<Predicate> predicates = domain->predicates;
    unordered_map<string, unsigned int> predicateMap = domain->predicateMap;
    unordered_map<unsigned int, unordered_set<unsigned int>> unaryFacts = problem->initState.unaryFacts;

    GenerateUnaryFacts(macros, problem, &predicateMap, &unaryFacts, &predicates);
    GenerateMacroActions(macros, problem, &predicateMap, &actions);

    Domain *newDomain = new Domain(domain->name, domain->requirements, predicates, predicateMap, actions);

    Problem *newProblem = new Problem(
        problem->name, 
        newDomain, 
        problem->objects, 
        problem->objectMap, 
        State(unaryFacts, problem->initState.binaryFacts), 
        problem->goalState);

    return Instance(newDomain, newProblem);
}

void Instantiator::GenerateUnaryFacts(
        const vector<Macro>* macros,
        const Problem* problem,
        unordered_map<string, unsigned int>* predicateMap,
        unordered_map<unsigned int, unordered_set<unsigned int>>* unaryFacts,
        vector<Predicate>* predicates)
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
            predicates->push_back(Predicate(predicate, {"?x"}, 1));
        }
    }
}

void Instantiator::GenerateMacroActions(
    const vector<Macro>* macros,
    const Problem* problem,
    const unordered_map<string, unsigned int>* predicateMap,
    vector<Action>* actions) 
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

        vector<Literal> preconditions = GenerateLiterals(&macro->groundedAction.preconditions, &groundedToIndex);
        AppendObjectPreconditions(&preconditions, predicateMap, &parameters);
        vector<Literal> effects = GenerateLiterals(&macro->groundedAction.effects, &groundedToIndex);
        actions->push_back(Action(macro->name, parameters, preconditions, effects));
    }
}

vector<Literal> Instantiator::GenerateLiterals(
        const unordered_map<GroundedLiteral, bool> *groundedLiterals, 
        unordered_map<unsigned int, unsigned int> *groundedToIndex) 
{
    vector<Literal> literals; 
    literals.reserve(groundedLiterals->size());
    for (auto iter = groundedLiterals->begin(); iter != groundedLiterals->end(); iter++) {
        vector<unsigned int> args; 
        args.reserve((*iter).first.objects.size());
        for (int i = 0; i < (*iter).first.objects.size(); i++)
            args.push_back(groundedToIndex->at((*iter).first.objects.at(i)));
        literals.push_back(Literal((*iter).first.predicate, args, (*iter).second));
    }
    return literals;
}

void Instantiator::AppendObjectPreconditions(
        vector<Literal> *literals, 
        const unordered_map<string, unsigned int>* predicateMap,
        const vector<string>* parameters) 
{
    for (unsigned int i = 0; i < parameters->size(); i++) {
        string object = parameters->at(i).substr(1);
        string predicate = "IS-" + object;
        literals->push_back(Literal(predicateMap->at(predicate), vector<unsigned int>{ i }, true));
    }
}