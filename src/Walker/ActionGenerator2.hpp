#ifndef ACTION_GENERATOR2
#define ACTION_GENERATOR2

#include <vector>
#include <string>
#include <map>
#include <set>
#include <iterator>

#include "../PDDL/ActionInstance.hh"
#include "../PDDL/Instance.hh"
#include "../Helpers/AlgorithmHelper.hh"

#define MAXPARAMSIZE 12
#define TEMPOBJSIZE 32

class ActionGenerator2 {
public:
    unsigned int GetTotalActionsGenerated() { return totalActions; };
    ActionGenerator2(const std::vector<PDDL::Action>* actions, const unsigned int objectCount) : actions(actions) {
        for (int i = 0; i < objectCount; i++)
            objects.emplace(i);
    };

    std::vector<PDDL::ActionInstance> GenerateActions(const PDDL::State *state);
private:
    unsigned int totalActions = 0;
    std::unordered_set<unsigned int> objects;
    const std::vector<PDDL::Action> *actions;

    std::vector<PDDL::ActionInstance> GenerateActions(const PDDL::Action* action, const PDDL::State* state);
    void GetCandidates(std::set<std::array<unsigned int, MAXPARAMSIZE>>* candidates, const PDDL::State* state, const std::array<unsigned int, MAXPARAMSIZE> parentValues, const int currentIndex, const int maxIndex);
    bool IsBinaryLegal(const PDDL::State* state, const std::array<unsigned int, MAXPARAMSIZE>* set, const int currentMax);

    const std::vector<PDDL::Literal>* UnaryActionLiteralsPtr;
    const std::vector<PDDL::Literal>* BinaryActionLiteralsPtr;
};

#endif
