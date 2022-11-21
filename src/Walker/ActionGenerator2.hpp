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
#define TEMPOBJSIZE 32

class ActionGenerator2 {
public:
    unsigned int GetTotalActionsGenerated() { return totalActions; };
    ActionGenerator2(const std::vector<PDDLAction>* actions) : actions(actions) {};

    std::vector<PDDLActionInstance> GenerateActions(const PDDLState *state);


    std::vector<PDDLActionInstance> GenerateActions(const PDDLAction *action, const PDDLState *state);
    void GetCandidates(std::set<std::array<unsigned int, MAXPARAMSIZE>>* candidates, const PDDLState* state, std::array<unsigned int, MAXPARAMSIZE> parentValues, const int currentIndex, const int maxIndex);
    bool IsBinaryLegal(const PDDLState* state, std::array<unsigned int, MAXPARAMSIZE>* set, const int currentMax);
    void SetupActionLiteralsCache(const PDDLAction* action);
    bool Contains(const std::array<unsigned int, MAXPARAMSIZE> values, const unsigned int value, const int limit);

private:
    unsigned int totalActions = 0;
    const std::vector<PDDLAction> *actions;

    std::vector<PDDLLiteral> UnaryActionLiterals;
    std::vector<PDDLLiteral>* UnaryActionLiteralsPtr;
    std::vector<PDDLLiteral> BinaryActionLiterals;
    std::vector<PDDLLiteral>* BinaryActionLiteralsPtr;
};

#endif
