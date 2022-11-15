#ifndef ACTION_GENERATOR_REGRESSING
#define ACTION_GENERATOR_REGRESSING

#include "BaseActionGenerator.hpp"

#include <vector>

class ActionGeneratorRegressing : public BaseActionGenerator {
public:
    ActionGeneratorRegressing(const PDDLInstance *instance) : BaseActionGenerator(instance) {}

    std::vector<PDDLActionInstance> GenerateActions(const PDDLState *state) override;

private:

};

#endif