#ifndef BASEWALKER_HH
#define BASEWALKER_HH

#include <vector>
#include <list>

#include "../IntermediatePDDL/PDDLActionInstance.hh"
#include "Path.hh"
#include "Heuristics/BaseHeuristic.hh"
#include "DepthFunctions/BaseDepthFunction.hh"
#include "WidthFunctions/BaseWidthFunction.hh"
#include "ActionGenerator.hpp"

#include "../Config/Config.hh"
#include "../Helpers/Hashes.hh"

namespace std {
    template <>
    struct hash<Path> {
        auto operator()(const Path& s) const -> size_t {
            std::size_t seed = s.steps.size();
            for (auto& i : s.steps) {
                seed ^= hash<PDDLActionInstance>{}(i)+0x9e3779b9 + (seed << 6) + (seed >> 2);
            }
            return seed;
        }
    };
}

class BaseWalker {
public:
    std::string WalkerName;

    BaseHeuristic* heuristic;
    BaseDepthFunction* depthFunc;
    BaseWidthFunction* widthFunc;
    bool SaveStates = false;

    BaseWalker(std::string walkerName, PDDLInstance* instance, BaseHeuristic* heuristic, BaseWidthFunction* widthFunc) :
        WalkerName(walkerName), 
        instance(instance), 
        actionGenerator(ActionGenerator(&instance->domain->actions, instance->problem->objects.size())), 
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

    std::function<const void(PDDLInstance* instance, PDDLState* state)> OnTempStateMade;
    std::function<const void(PDDLInstance* instance, PDDLState* state, PDDLActionInstance* chosenAction)> OnStateWalk;

protected:
    unsigned int _totalIterations = 0;
    PDDLInstance* instance;
    ActionGenerator actionGenerator;
};

#endif
