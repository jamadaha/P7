
#ifndef PARTIAL_ACTION_CONVERTER
#define PARTIAL_ACTION_CONVERTER

#include <unordered_set>
#include <unordered_map>

#include "../../IntermediatePDDL/PDDLInstance.hh"

#include "PartialAction.hh"

// Assumes no static facts in state
class PartialActionConverter {
public:
    static const int MAX_PARAMETER_COUNT = 8;
    PartialActionConverter(const PDDLInstance *instance) : instance(instance) {
        for (unsigned int i = 0; i < instance->problem->objects.size(); i++)
            objects.emplace(i);
    };
    std::vector<PDDLActionInstance> ConvertAction(const PDDLState *state, const PartialAction *action);
    
    
private:
    const PDDLInstance *instance;
    std::unordered_set<unsigned int> objects;

    std::unordered_set<unsigned int> GetParameterCandidates(const PDDLState *state, const PartialAction *action, const unsigned int paramIndex);
    std::vector<std::vector<unsigned int>> PermuteAll(const std::unordered_set<unsigned int> parameterObjects[], const unsigned int paramCount);
    bool Permute(   const std::unordered_set<unsigned int> parameterObjects[],
                    std::vector<std::vector<unsigned int>> *permutations, 
                    std::vector<unsigned int> *permutation, 
                    const unsigned int paramCount);
};

#endif
