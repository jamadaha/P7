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
    BaseActionGenerator(const std::vector<PDDLAction> *actions, const unsigned int objectCount) : actions(actions) {
        for (int i = 0; i < objectCount; i++)
            objects.emplace(i);
    };

    virtual std::vector<PDDLActionInstance> GenerateActions(const PDDLState *state) = 0;

protected:
    unsigned int totalActions = 0;
    const std::vector<PDDLAction> *actions;
    std::unordered_set<unsigned int> objects;
};

#endif
