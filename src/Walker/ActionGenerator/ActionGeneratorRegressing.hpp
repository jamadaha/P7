#ifndef ACTION_GENERATOR_REGRESSING
#define ACTION_GENERATOR_REGRESSING

#include "BaseActionGenerator.hpp"

class ActionGeneratorRegressing : public BaseActionGenerator {
public:
    ActionGeneratorRegressing(const std::vector<PDDLAction> *actions, const unsigned int objectCount) : BaseActionGenerator(actions, objectCount) {}

    std::vector<PDDLAction> GenerateActions() {

    }
};

#endif