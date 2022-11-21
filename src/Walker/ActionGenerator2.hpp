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

#define MAXPARAMSIZE 12

class ActionGenerator2 {
public:
    unsigned int GetTotalActionsGenerated() { return totalActions; };
    ActionGenerator2(const std::vector<PDDLAction>* actions) : actions(actions) {};

    std::vector<PDDLActionInstance> GenerateActions(const PDDLState *state);


    std::vector<PDDLActionInstance> GenerateActions(const PDDLAction *action, const PDDLState *state);
    std::set<std::array<unsigned int, MAXPARAMSIZE>> GetCandidates(const PDDLState* state, std::array<unsigned int, MAXPARAMSIZE> parentValues, const int currentIndex, const int maxIndex);
    bool IsBinaryLegal(const PDDLState* state, std::array<unsigned int, MAXPARAMSIZE>* set, const int currentMax);
    std::set<std::array<unsigned int, MAXPARAMSIZE>> GetInitialParameterValue(const PDDLState* state);
    void SetupActionLiteralsCache(const PDDLAction* action);
    bool Contains(std::array<unsigned int, MAXPARAMSIZE> values, unsigned int value);

private:
    unsigned int totalActions = 0;
    const std::vector<PDDLAction> *actions;

    std::vector<PDDLLiteral> UnaryActionLiterals;
    std::vector<PDDLLiteral> BinaryActionLiterals;
};

#endif
