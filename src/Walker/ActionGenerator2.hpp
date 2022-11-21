#ifndef ACTION_GENERATOR2
#define ACTION_GENERATOR2

#include <vector>
#include <string>
#include <map>
#include <set>
#include <iterator>

#include "../IntermediatePDDL/PDDLActionInstance.hh"
#include "../IntermediatePDDL/PDDLInstance.hh"
#include "../Helpers/AlgorithmHelper.hh"

class ActionGenerator2 {
public:
    unsigned int GetTotalActionsGenerated() { return totalActions; };
    ActionGenerator2(const std::vector<PDDLAction>* actions) : actions(actions) {};

    std::vector<PDDLActionInstance> GenerateActions(const PDDLState *state);
    std::vector<PDDLActionInstance> GenerateActions(const PDDLAction *action, const PDDLState *state);
    std::unordered_set<std::vector<unsigned int>> GetCandidates(const PDDLAction* action, const PDDLState* state, std::vector<unsigned int> parentValues);

private:
    unsigned int totalActions = 0;
    const std::vector<PDDLAction> *actions;
};

#endif
