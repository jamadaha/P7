#include "PartialActionConverter.hh"

std::vector<PDDLActionInstance> PartialActionConverter::ConvertAction(const PDDLState *state, const PartialAction *action) {
    if (action->parameters.size() > MAX_PARAMETER_COUNT)
        throw std::logic_error("Parameter count exceeded max");

    std::vector<PDDLActionInstance> actions;
    std::unordered_set<unsigned int> parameterCandidates[MAX_PARAMETER_COUNT];
    for (int i = 0; i < action->parameters.size(); i++) {
        if (action->parameters.at(i) != nullptr)
            parameterCandidates[i] = std::unordered_set<unsigned int>{ *action->parameters.at(i) };
        else
            parameterCandidates[i] = GetParameterCandidates(state, action, i);
    }


    return actions;
}

std::unordered_set<unsigned int> PartialActionConverter::GetParameterCandidates(const PDDLState *state, const PartialAction *action, const unsigned int paramIndex) {
    std::vector<const PDDLLiteral*> unaryStaticLiterals;
    std::unordered_set<unsigned int> candidateObjects = objects;
    for (auto iter = action->action->applicableUnaryLiterals.at(paramIndex).begin(); iter != action->action->applicableUnaryLiterals.at(paramIndex).end(); iter++)
        if (instance->domain->staticPredicates.contains((*iter)->predicateIndex)) {
            if ((*iter)->args.size() == 1)
                unaryStaticLiterals.push_back(*iter);
            else
                throw std::logic_error("Not implemented");
        }
    if (unaryStaticLiterals.size() > 0) {
        for (int i = 0; i < unaryStaticLiterals.size(); i++) {
            auto literal = unaryStaticLiterals.at(i);
            auto applicableFacts = instance->problem->initState.unaryFacts.at(literal->predicateIndex);
            if (literal->value)
                AlgorithmHelper::Intersect(candidateObjects, applicableFacts);
            else
                AlgorithmHelper::Difference(candidateObjects, applicableFacts);
        }
    } else {
        throw std::logic_error("Not implemented");
    }
    return candidateObjects;
}

 std::vector<std::array<unsigned int, PartialActionConverter::MAX_PARAMETER_COUNT>> PartialActionConverter::PermuteAll(std::unordered_set<unsigned int> parameterObjects[]) {
    std::vector<std::array<unsigned int, MAX_PARAMETER_COUNT>> permutations;
    for (auto iter = parameterObjects[0].begin(); iter != parameterObjects[0].end(); iter++) {
        unsigned int rootArray[MAX_PARAMETER_COUNT] = { *iter };
        std::array<unsigned int, MAX_PARAMETER_COUNT> result =  Permute(parameterObjects, rootArray, 1);
        for (int i = 0; i < result.size(); i++)
            permutations.push_back(result);
    }
    return permutations;
 }

std::array<unsigned int, PartialActionConverter::MAX_PARAMETER_COUNT> PartialActionConverter::Permute(std::unordered_set<unsigned int> parameterObjects[], unsigned int permutation[], const unsigned int workingIndex) {
    printf("\n");
}
