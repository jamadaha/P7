
#ifndef PARTIAL_ACTION_CONVERTER
#define PARTIAL_ACTION_CONVERTER

#include <unordered_set>

#include "../../IntermediatePDDL/PDDLAction.hh"
#include "../../IntermediatePDDL/PDDLActionInstance.hh"
#include "../../IntermediatePDDL/PDDLState.hh"
#include "../../IntermediatePDDL/PDDLInstance.hh"

#include "PartialAction.hh"

// Assumes no static facts in state
class PartialActionConverter {
public:
    PartialActionConverter(const std::vector<PDDLAction> *actions, const unsigned int objectCount) : actions(actions), objects(GetObjects(objectCount)) {};
    std::vector<PDDLActionInstance> ConvertAction(const PDDLState *state, const PartialAction *action);
    
    
private:
    const std::vector<PDDLAction> *actions;
    const std::unordered_set<unsigned int> objects;

    std::unordered_set<unsigned int> GetObjects(const unsigned int objectCount) {
        std::unordered_set<unsigned int> tempObjects;
        tempObjects.reserve(objectCount);
        for (unsigned int i = 0; i < objectCount; i++)
            tempObjects.emplace(i);
        return tempObjects;
    }

    std::unordered_set<unsigned int> GetParameterCandidates(const PDDLState *state, const PartialAction *action, const unsigned int paramIndex);
};

#endif
