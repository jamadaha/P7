#include "PartialActionConverter.hh"

std::vector<PDDLActionInstance> PartialActionConverter::ConvertAction(const PDDLState *state, const PartialAction *action) {
    if (action->parameters.size() > MAX_PARAMETER_COUNT)
        throw std::logic_error("Parameter count exceeded max");

    std::unordered_set<unsigned int> parameterCandidates[MAX_PARAMETER_COUNT];
    for (int i = 0; i < action->parameters.size(); i++) {
        if (action->parameters.at(i) != nullptr)
            parameterCandidates[i] = std::unordered_set<unsigned int>{ *action->parameters.at(i) };
        else
            parameterCandidates[i] = GetParameterCandidates(state, action, i);
    }

    auto permutations = PermuteAll(parameterCandidates, action->parameters.size());

    std::vector<PDDLActionInstance> actions;
    for (int i = 0; i < permutations.size();  i++)
        actions.push_back(PDDLActionInstance(action->action, permutations.at(i)));

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

std::vector<std::vector<unsigned int>> PartialActionConverter::PermuteAll(const std::unordered_set<unsigned int> parameterObjects[], const unsigned int paramCount) {
    std::vector<std::vector<unsigned int>> permutations;
    
    for (auto iter = parameterObjects[0].begin(); iter != parameterObjects[0].end(); iter++) {
        std::vector<unsigned int> permutation{ *iter };
        if (!Permute(parameterObjects, &permutations, &permutation, paramCount))
            return std::vector<std::vector<unsigned int>>();
        
    }
    return permutations;
}
bool PartialActionConverter::Permute(const std::unordered_set<unsigned int> parameterObjects[],
             std::vector<std::vector<unsigned int>> *permutations, 
             std::vector<unsigned int> *permutation, 
             const unsigned int paramCount) 
{
    const unsigned int workingIndex = permutation->size();
    if (workingIndex == paramCount) {
        permutations->push_back(*permutation);
        return true;
    } else if (parameterObjects[workingIndex].size() == 0)
        return false;

    for (auto iter = parameterObjects[workingIndex].begin(); iter != parameterObjects[workingIndex].end(); iter++) {
        permutation->push_back(*iter);

        Permute(parameterObjects, permutations, permutation, paramCount);

        permutation->pop_back();
    }

    return true;
}
