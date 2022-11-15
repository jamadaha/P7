#ifndef ACTION_GENERATOR_REGRESSING
#define ACTION_GENERATOR_REGRESSING

#include "BaseActionGenerator.hpp"

#include <vector>
#include <unordered_map>

class ActionGeneratorRegressing : public BaseActionGenerator {
public:
    ActionGeneratorRegressing(const PDDLInstance *instance) : BaseActionGenerator(instance) {}

    std::vector<PDDLActionInstance> GenerateActions(const PDDLState *state) override;
    std::vector<PDDLActionInstance> GenerateActionsFromUnary(const PDDLState *state, const unsigned int predicate, const unsigned int object);
    std::vector<PDDLActionInstance> GenerateActionsFromBinary(const PDDLState *state, const unsigned int predicate, const std::pair<unsigned int, unsigned int> objects);

    std::vector<PDDLActionInstance> GenerateFromPartial(const PDDLState *state, const PDDLAction *action, const std::unordered_map<unsigned int, unsigned int> partialParameters);
};

#endif