#ifndef BASEWALKER_HH
#define BASEWALKER_HH

#include <vector>
#include <list>

#include "../PDDL/ActionInstance.hh"
#include "Path.hh"
#include "Heuristics/BaseHeuristic.hh"
#include "DepthFunctions/BaseDepthFunction.hh"
#include "WidthFunctions/BaseWidthFunction.hh"
#include "ActionGenerator.hpp"
#include "ActionGenerator2.hpp"

#include "../Config/Config.hh"
#include "../Helpers/Hashes.hh"

class BaseWalker {
public:
    std::string WalkerName;

    BaseHeuristic* heuristic;
    BaseDepthFunction* depthFunc;
    BaseWidthFunction* widthFunc;
    bool SaveStates = false;

    BaseWalker(std::string walkerName, PDDL::Instance* instance, BaseHeuristic* heuristic, BaseWidthFunction* widthFunc) :
        WalkerName(walkerName), 
        instance(instance), 
        actionGenerator(ActionGenerator2(&instance->domain->actions, instance->problem->objects.size())),
        //actionGenerator(ActionGenerator(&instance->domain->actions, instance->problem->objects.size())),
        heuristic(heuristic), widthFunc(widthFunc) {}
    ~BaseWalker() {
        free(heuristic);
        free(widthFunc);
    }

    virtual std::vector<Path> Walk() = 0;
    unsigned int GetTotalActionsGenerated() { return actionGenerator.GetTotalActionsGenerated(); };
    unsigned int GetTotalIterations() { return _totalIterations; };

    std::function<const void(BaseWalker* sender)> OnWalkerStart;
    std::function<const void(BaseWalker* sender, int currentStep)> OnWalkerStep;
    std::function<const void(BaseWalker* sender, int timeTaken)> OnWalkerEnd;

    std::function<const void(PDDL::Instance* instance, PDDL::State* state)> OnTempStateMade;
    std::function<const void(PDDL::Instance* instance, PDDL::State* state, PDDL::ActionInstance* chosenAction)> OnStateWalk;

protected:
    unsigned int _totalIterations = 0;
    PDDL::Instance* instance;
    ActionGenerator2 actionGenerator;
    //ActionGenerator actionGenerator;
};

#endif
