#include "ExternalParser.hh"
#include "../PDDL/Parsers/ExternalParser/pddldriver.hh"
#include "ExternalParser/domain.hh"
#include "ExternalParser/problem.hh"

#pragma region Converter

std::vector<PDDL::Literal> GetLiteralList(
    std::unordered_map<std::string, unsigned int> predicateMap,
    std::unordered_map<std::string, unsigned int> parameterIndex,
    const std::vector<std::pair<Predicate*, bool>*>* input)
{
    std::vector<PDDL::Literal> literals;
    literals.reserve(input->size());
    for (int i = 0; i < input->size(); i++) {
        std::vector<unsigned int> args;
        auto precondition = (*input)[i];
        args.reserve(precondition->first->_args->size());
        for (int a = 0; a < precondition->first->_args->size(); a++)
            args.push_back(parameterIndex[(*precondition->first->_args)[a]]);

        literals.push_back(PDDL::Literal(predicateMap[StringHelper::ToUpper(precondition->first->_name)], args, precondition->second));
    }
    return literals;
}

PDDL::Action GenerateAction(
    std::string name,
    const StringList* parameters,
    const PreconditionList* preconditions,
    const EffectList* effects,
    std::unordered_map<std::string, unsigned int> predicateMap)
{
    std::vector<std::string> tempParameters;
    tempParameters.reserve(parameters->size());

    std::unordered_map<std::string, unsigned int> parameterIndex;
    parameterIndex.reserve(parameters->size());

    // Get index of each paramter
    // ?x, ?y ... => 0, 1
    for (int i = 0; i < parameters->size(); i++) {
        parameterIndex.emplace((*parameters)[i], i);
        tempParameters.push_back((*parameters)[i]);
    }

    std::vector<PDDL::Literal> tempPreconditions = GetLiteralList(predicateMap, parameterIndex, preconditions);
    std::vector<PDDL::Literal> tempEffects = GetLiteralList(predicateMap, parameterIndex, effects);

    return PDDL::Action(name, tempParameters, tempPreconditions, tempEffects);
}

std::unordered_map<unsigned int, std::unordered_set<unsigned int>> GetUnaryFacts(
    PDDL::Domain* domain,
    std::unordered_map<std::string, unsigned int>* objectMap,
    LiteralList* literalList)
{
    std::unordered_map<unsigned int, std::unordered_set<unsigned int>> unaryFacts;
    for (int i = 0; i < domain->predicates.size(); i++)
        if (domain->predicates[i].argumentCount == 1)
            unaryFacts[i] = std::unordered_set<unsigned int>();

    for (int i = 0; i < literalList->size(); i++) {
        auto fact = (*literalList)[i];
        if (fact->first->_args->size() != 1)
            continue;
        unsigned int predicateIndex = domain->predicateMap.at(StringHelper::ToUpper(fact->first->_name));
        unsigned int objectIndex = objectMap->at(StringHelper::ToUpper((*fact->first->_args)[0]));
        unaryFacts.at(predicateIndex).emplace(objectIndex);
    }
    return unaryFacts;
};

std::unordered_map<unsigned int, std::unordered_set<std::pair<unsigned int, unsigned int>>> GetBinaryFacts(
    PDDL::Domain* domain,
    std::unordered_map<std::string, unsigned int>* objectMap,
    LiteralList* literalList)
{
    std::unordered_map<unsigned int, std::unordered_set<std::pair<unsigned int, unsigned int>>> binaryFacts;
    for (int i = 0; i < domain->predicates.size(); i++)
        if (domain->predicates[i].argumentCount > 1)
            binaryFacts[i] = std::unordered_set<std::pair<unsigned int, unsigned int>>();

    for (int i = 0; i < literalList->size(); i++) {
        auto fact = (*literalList)[i];
        if (fact->first->_args->size() != 2)
            continue;
        unsigned int predicateIndex = domain->predicateMap.at(StringHelper::ToUpper(fact->first->_name));
        binaryFacts.at(predicateIndex).emplace(
            std::make_pair(objectMap->at(StringHelper::ToUpper((*fact->first->_args)[0])),
                objectMap->at(StringHelper::ToUpper((*fact->first->_args)[1]))));
    }
    return binaryFacts;
}

PDDL::Domain Convert(Domain* domain) {
    std::string name = domain->_name.c_str();

    // Get Requirements
    std::vector<std::string> requirements;
    requirements.reserve(domain->_requirements->size());
    for (int i = 0; i < domain->_requirements->size(); i++)
        requirements.push_back((*domain->_requirements)[i]);

    // Get Predicates
    std::vector<PDDL::Predicate> predicates;
    std::unordered_map<std::string, unsigned int> predicateMap;
    predicates.reserve(domain->_predicates->size());
    predicateMap.reserve(domain->_predicates->size());

    // Don't question it
    auto AddPredicate = [&](PDDL::Predicate predicate) {
        predicateMap.emplace(predicate.name, predicates.size());
        predicates.push_back(predicate);
    };

    AddPredicate(PDDL::Predicate("=", {"?x", "?y"}, 2));

    for (int i = 0; i < domain->_predicates->size(); i++) {
        auto predicate = (*domain->_predicates)[i];
        AddPredicate(PDDL::Predicate(StringHelper::ToUpper(predicate->_name), (*predicate->_args), predicate->_args->size()));
    }

    // Get Actions
    std::vector<PDDL::Action> actions;
    actions.reserve(domain->_actions->size());
    for (int i = 0; i < domain->_actions->size(); i++) {
        auto action = (*domain->_actions)[i];
        actions.push_back(GenerateAction(action->_name, action->_params, action->_precond, action->_effects, predicateMap));
    }

    return PDDL::Domain(name, requirements, predicates, predicateMap, actions);
}

PDDL::Problem Convert(PDDL::Domain* domain, Problem* problem) {
    std::string name = problem->_name;

    // Get Objects
    std::vector<std::string> objects;
    std::unordered_map<std::string, unsigned int> objectMap;
    objects.reserve(problem->_objects->size());
    objectMap.reserve(problem->_objects->size());
    for (int i = 0; i < problem->_objects->size(); i++) {
        objectMap.emplace(StringHelper::ToUpper((*problem->_objects)[i]), i);
        objects.push_back(StringHelper::ToUpper((*problem->_objects)[i]));
    }

    // Get Init and Goal state
    auto initUnaryFacts = GetUnaryFacts(domain, &objectMap, problem->_init);
    auto goalUnaryFacts = GetUnaryFacts(domain, &objectMap, problem->_goal);
    auto initBinaryFacts = GetBinaryFacts(domain, &objectMap, problem->_init);
    auto goalBinaryFacts = GetBinaryFacts(domain, &objectMap, problem->_goal);

    auto initState = PDDL::State(initUnaryFacts, initBinaryFacts);
    auto goalState = PDDL::State(goalUnaryFacts, goalBinaryFacts);

    return PDDL::Problem(name, domain, objects, objectMap, initState, goalState);
}

#pragma endregion

PDDL::Instance ExternalParser::Parse(const std::string& domainFile, const std::string& problemFile) {
    PDDLDriver driver;
    if (driver.parse(domainFile))
        throw std::invalid_argument("Invalid domain file!");
    if (driver.parse(problemFile))
        throw std::invalid_argument("Invalid problem file!");

    static PDDL::Domain domain = Convert(driver.domain);
    static PDDL::Problem problem = Convert(&domain, driver.problem);

    return PDDL::Instance(&domain, &problem);
}
