#ifndef PARTIAL_ACTION_GENERATOR
#define PARTIAL_ACTION_GENERATOR

#include <unordered_set>

#include "../../IntermediatePDDL/PDDLAction.hh"
#include "../../IntermediatePDDL/PDDLState.hh"

#include "PartialAction.hh"

// Assumes no static facts in state
class PartialActionGenerator {
public:
    PartialActionGenerator(const std::vector<PDDLAction> *actions, const unsigned int objectCount) : actions(actions), objects(GetObjects(objectCount)) {};
    // Expands the state, I.e. generates all actions which makes atleast one of the facts true
    std::unordered_set<PartialAction> ExpandState(const PDDLState *state);
    // Same as ExpandState, except it only generates a single of those actions
    PartialAction ExpandStateSingle(const PDDLState *state);
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
    std::unordered_set<PartialAction> ExpandUnary(std::pair<unsigned int, unsigned int> predicateObject);
    std::unordered_set<PartialAction> ExpandBinary(std::pair<unsigned int, std::pair<unsigned int, unsigned int>> predicateObjects);

    PartialAction CreateFromUnary(const PDDLAction *action, const unsigned int index, const unsigned int object);
    PartialAction CreateFromBinay(const PDDLAction *action, const std::pair<unsigned int, unsigned int> indexes, const std::pair<unsigned int, unsigned int> objects);
};

#endif
