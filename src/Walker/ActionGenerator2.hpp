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
    ActionGenerator2(const std::vector<PDDLAction>* actions, const unsigned int objectCount) : actions(actions) {
        for (int i = 0; i < objectCount; i++)
            objects.emplace(i);
    };

    std::vector<PDDLActionInstance> GenerateActions(const PDDLState *state);
private:
    unsigned int totalActions = 0;
    std::unordered_set<unsigned int> objects;
    const std::vector<PDDLAction> *actions;

    std::vector<PDDLActionInstance> GenerateActions(const PDDLAction* action, const PDDLState* state);
    void GetCandidates(std::set<std::array<unsigned int, MAXPARAMSIZE>>* candidates, const PDDLState* state, const std::array<unsigned int, MAXPARAMSIZE> parentValues, const int currentIndex, const int maxIndex);
    bool IsBinaryLegal(const PDDLState* state, const std::array<unsigned int, MAXPARAMSIZE>* set, const int currentMax);

    const std::vector<PDDLLiteral>* UnaryActionLiteralsPtr;
    const std::vector<PDDLLiteral>* BinaryActionLiteralsPtr;
};

#endif
