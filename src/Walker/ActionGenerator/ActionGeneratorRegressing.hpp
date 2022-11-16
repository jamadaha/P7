#ifndef ACTION_GENERATOR_REGRESSING
#define ACTION_GENERATOR_REGRESSING

#include "BaseActionGenerator.hpp"

#include <vector>
#include <unordered_map>
#include <map>

class ActionGeneratorRegressing : public BaseActionGenerator {
public:
    ActionGeneratorRegressing(const PDDLInstance *instance) : BaseActionGenerator(instance) {}

    PDDLActionInstance GenerateRandomAction(const PDDLState *state) override;

    std::vector<PDDLActionInstance> GenerateActions(const PDDLState *state) override;
    std::vector<PDDLActionInstance> GenerateActionsFromUnary(const PDDLState *state, const unsigned int predicate, const unsigned int object);
    std::vector<PDDLActionInstance> GenerateActionsFromBinary(const PDDLState *state, const unsigned int predicate, const std::pair<unsigned int, unsigned int> objects);

    std::vector<PDDLActionInstance> GenerateFromPartial(const PDDLState *state, const PDDLAction *action, const std::map<unsigned int, unsigned int> partialParameters);

    std::unordered_set<unsigned int> GetCandidateObjects(const PDDLState *state, const PDDLAction *action, const unsigned int *index);
    // The index of some precondition refers to a static predicate
    const PDDLLiteral* IsParamStatic(const PDDLAction *action, const unsigned int *index);

    std::unordered_map<std::pair<unsigned int, unsigned int>, std::unordered_set<std::pair<unsigned int, unsigned int>>> 
    GenerateLegalPairings(const PDDLState *state, const PDDLAction *action, std::vector<std::unordered_set<unsigned int>> *candidateObjects);
};

#endif