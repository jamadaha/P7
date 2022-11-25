#ifndef PARTIAL_ACTION_GENERATOR
#define PARTIAL_ACTION_GENERATOR

#include <unordered_set>

#include "../../IntermediatePDDL/PDDLAction.hh"
#include "../../IntermediatePDDL/PDDLState.hh"
#include "../../IntermediatePDDL/PDDLInstance.hh"

#include "PartialAction.hh"

// Assumes no static facts in state
class PartialActionGenerator {
public:
    PartialActionGenerator(const std::vector<PDDLAction> *actions, const unsigned int objectCount) : actions(actions), objects(GetObjects(objectCount)) {};
    // Expands the state, I.e. generates all actions which makes atleast one of the facts true
    std::vector<PartialAction> ExpandState(const PDDLState *state);
    void FillPartialAction(const PDDLInstance *instance, PartialAction *partialAction);
    PDDLActionInstance ConvertPartialAction(const PDDLInstance *instance, const PartialAction *partialAction);
    
    
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
    std::vector<PartialAction> ExpandUnary(std::pair<unsigned int, unsigned int> predicateObject);
    std::vector<PartialAction> ExpandBinary(std::pair<unsigned int, std::pair<unsigned int, unsigned int>> predicateObjects);

    PartialAction CreateFromUnary(const PDDLAction *action, const unsigned int index, const unsigned int object);
    PartialAction CreateFromBinay(const PDDLAction *action, const std::pair<unsigned int, unsigned int> indexes, const std::pair<unsigned int, unsigned int> objects);

    unsigned int GetParameterCandidate(const PDDLInstance *instance, const PDDLAction *action, const unsigned int *paramIndex);
    std::unordered_set<unsigned int> GetParameterCandidates(const PDDLInstance *instance, const PDDLAction *action, const unsigned int *paramIndex);
};

#endif
