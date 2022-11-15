#ifndef BASE_ACTION_GENERATOR
#define BASE_ACTION_GENERATOR

#include <vector>
#include <string>
#include <map>
#include <set>
#include <iterator>

#include "../../IntermediatePDDL/PDDLActionInstance.hh"
#include "../../IntermediatePDDL/PDDLInstance.hh"

class BaseActionGenerator {
public:
    unsigned int GetTotalActionsGenerated() { return totalActions; };
    BaseActionGenerator(const PDDLInstance *instance) : instance(instance) {};

    virtual std::vector<PDDLActionInstance> GenerateActions(const PDDLState *state) = 0;

protected:
    const PDDLInstance *instance;
    unsigned int totalActions = 0;
};

#endif