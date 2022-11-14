#include "PDDLConverter.hh"

PDDLDomain PDDLConverter::Convert(Domain *domain) {
    std::string name = domain->_name.c_str();

    // Get Requirements
    std::vector<std::string> requirements;
    requirements.reserve(domain->_requirements->size());
    for (int i = 0; i < domain->_requirements->size(); i++)
        requirements.push_back((*domain->_requirements)[i]);

    // Get Predicates
    std::vector<PDDLPredicate> predicates;
    std::unordered_map<std::string, unsigned int> predicateMap;
    predicates.reserve(domain->_predicates->size());
    predicateMap.reserve(domain->_predicates->size());
    
    // Don't question it
    auto AddPredicate = [&](PDDLPredicate predicate) {
        predicateMap.emplace(predicate.name, predicates.size());
        predicates.push_back(predicate);
    };

    AddPredicate(PDDLPredicate("=", std::vector<std::string>{}, 2));

    for (int i = 0; i < domain->_predicates->size(); i++) {
        auto predicate = (*domain->_predicates)[i];
        AddPredicate(PDDLPredicate(StringHelper::ToUpper(predicate->_name), (*predicate->_args), predicate->_args->size()));
    }    

    // Get Actions
    std::vector<PDDLAction> tempActions;
    tempActions.reserve(domain->_actions->size());
    for (int i = 0; i < domain->_actions->size(); i++) {
        auto action = (*domain->_actions)[i];
        tempActions.push_back(GenerateAction(action->_name, action->_params, action->_precond, action->_effects, predicateMap));
    }
    auto staticPredicates = GetStaticPredicates(predicates.size(), tempActions);
    std::vector<PDDLAction> actions;
    for (int i = 0; i < tempActions.size(); i++)
        actions.push_back(PDDLAction(tempActions.at(i), &staticPredicates));

    return PDDLDomain(name, requirements, predicates, predicateMap, actions);
}

PDDLProblem PDDLConverter::Convert(PDDLDomain *domain, Problem *problem) {
    std::string name = problem->_name;

    // Get Objects
    std::vector<std::string> objects;
    std::unordered_map<std::string, unsigned int> objectMap;
    objects.reserve(problem->_objects->size());
    objectMap.reserve(problem->_objects->size());
    for (int i = 0; i < problem->_objects->size(); i++) {
        objectMap.emplace((*problem->_objects)[i], i);
        objects.push_back((*problem->_objects)[i]);
    }
    
    // Get Init and Goal state
    auto initUnaryFacts = GetUnaryFacts(domain, &objectMap, problem->_init);
    auto goalUnaryFacts = GetUnaryFacts(domain, &objectMap, problem->_goal);
    auto initBinaryFacts = GetBinaryFacts(domain, &objectMap, problem->_init);
    auto goalBinaryFacts = GetBinaryFacts(domain, &objectMap, problem->_goal);
    auto initMultiFacts = GetMultiFacts(domain, &objectMap, problem->_init);
    auto goalMultiFacts = GetMultiFacts(domain, &objectMap, problem->_goal);
    
    auto initState = PDDLState(initUnaryFacts, initBinaryFacts, initMultiFacts);
    auto goalState = PDDLState(goalUnaryFacts, goalBinaryFacts, goalMultiFacts);
    
    return PDDLProblem(name, domain, objects, objectMap, initState, goalState);
}

std::vector<PDDLLiteral> PDDLConverter::GetLiteralList(std::unordered_map<std::string, unsigned int> predicateMap, std::unordered_map<std::string, unsigned int> parameterIndex, const std::vector<std::pair<Predicate*,bool>*>* input) {
    std::vector<PDDLLiteral> literals;
    literals.reserve(input->size());
    for (int i = 0; i < input->size(); i++) {
        std::vector<unsigned int> args;
        auto precondition = (*input)[i];
        args.reserve(precondition->first->_args->size());
        for (int a = 0; a < precondition->first->_args->size(); a++)
            args.push_back(parameterIndex[(*precondition->first->_args)[a]]);

        literals.push_back(PDDLLiteral(predicateMap[StringHelper::ToUpper(precondition->first->_name)], args, precondition->second));
    }
    return literals;
}

PDDLAction PDDLConverter::GenerateAction(std::string name, const StringList *parameters, const PreconditionList *preconditions, const EffectList *effects, std::unordered_map<std::string, unsigned int> predicateMap) {
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
    
    std::vector<PDDLLiteral> tempPreconditions = GetLiteralList(predicateMap, parameterIndex, preconditions);
    std::vector<PDDLLiteral> tempEffects = GetLiteralList(predicateMap, parameterIndex, effects);

    return PDDLAction(name, tempParameters, tempPreconditions, tempEffects);
}

std::unordered_map<unsigned int, std::unordered_set<unsigned int>> PDDLConverter::GetUnaryFacts(PDDLDomain *domain, std::unordered_map<std::string, unsigned int> *objectMap, LiteralList *literalList) {
    std::unordered_map<unsigned int, std::unordered_set<unsigned int>> unaryFacts;
    for (int i = 0; i < domain->predicates.size(); i++)
        if (domain->predicates[i].argumentCount == 1)
            unaryFacts[i] = std::unordered_set<unsigned int>();

    for (int i = 0; i < literalList->size(); i++) {
        auto fact = (*literalList)[i];
        if (fact->first->_args->size() != 1)
            continue;
        unsigned int predicateIndex = domain->predicateMap.at(StringHelper::ToUpper(fact->first->_name));
        unsigned int objectIndex = objectMap->at((*fact->first->_args)[0]); 
        unaryFacts.at(predicateIndex).emplace(objectIndex);
    }
    return unaryFacts;
};

std::unordered_map<unsigned int, std::unordered_set<std::pair<unsigned int, unsigned int>>> PDDLConverter::GetBinaryFacts(PDDLDomain *domain, std::unordered_map<std::string, unsigned int> *objectMap, LiteralList *literalList) {
    std::unordered_map<unsigned int, std::unordered_set<std::pair<unsigned int, unsigned int>>> binaryFacts;
    for (int i = 0; i < domain->predicates.size(); i++)
        if (domain->predicates[i].argumentCount > 1)
            binaryFacts[i] = std::unordered_set<std::pair<unsigned int, unsigned int>>();

    for (int i = 0; i < literalList->size(); i++) {
        auto fact = (*literalList)[i];
        if (fact->first->_args->size() != 2)
            continue;
        unsigned int predicateIndex = domain->predicateMap.at(StringHelper::ToUpper(fact->first->_name));
        binaryFacts.at(predicateIndex).emplace(std::make_pair(objectMap->at((*fact->first->_args)[0]), objectMap->at((*fact->first->_args)[1])));
    }
    return binaryFacts;
}

std::unordered_map<unsigned int, std::unordered_set<MultiFact>> PDDLConverter::GetMultiFacts(PDDLDomain *domain, std::unordered_map<std::string, unsigned int> *objectMap, LiteralList *literalList) {
    std::unordered_map<unsigned int, std::unordered_set<MultiFact>> multiFacts;
    for (int i = 0; i < domain->predicates.size(); i++)
        if (domain->predicates[i].argumentCount > 2)
            multiFacts[i] = std::unordered_set<MultiFact>();

    for (int i = 0; i < literalList->size(); i++) {
        auto fact = (*literalList)[i];
        if (fact->first->_args->size() < 3)
            continue;
        unsigned int predicateIndex = domain->predicateMap.at(StringHelper::ToUpper(fact->first->_name));
        std::vector<unsigned int> objectIndexes;
        for (int a = 0; a < fact->first->_args->size(); a++)
            objectIndexes.push_back(objectMap->at((*fact->first->_args)[a]));
        multiFacts.at(predicateIndex).emplace(MultiFact(objectIndexes));
    }
    return multiFacts;
}
   
std::unordered_set<unsigned int> PDDLConverter::GetStaticPredicates(const unsigned int predicateCount, const std::vector<PDDLAction> actions) {
    std::unordered_set<unsigned int> candidateIndexes; candidateIndexes.reserve(predicateCount);
    for (int i = 1; i < predicateCount; i++)
        candidateIndexes.emplace(i);
    for (auto iter = actions.begin(); iter != actions.end(); iter++) {
        for (auto litIter = (*iter).effects.begin(); litIter != (*iter).effects.end(); litIter++) {
            if (candidateIndexes.contains((*litIter).predicateIndex))
                candidateIndexes.erase((*litIter).predicateIndex);
        }
    }
    return candidateIndexes;
}