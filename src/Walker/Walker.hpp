#ifndef WALKER
#define WALKER

#include <vector>

#include "../IntermediatePDDL/PDDLActionInstance.hh"
#include "Heuristics/BaseHeuristics.hh"
#include "Heuristics/Contexts/PDDLContext.hh"
#include "DepthFunctions/BaseDepthFunction.hh"
#include "DepthFunctions/ObjectActionDepthFunction.hh"
#include "ActionGenerator.hpp"
#include "../RunReport/RunReport.hh"

struct Path {
    const std::vector<PDDLActionInstance> steps;
    Path(std::vector<PDDLActionInstance> steps) : steps(steps) {};

    struct HashFunction {
        std::size_t operator()(Path const& s) const noexcept
        {
            auto a = PDDLActionInstance::HashFunction(s.steps[0]);
            return a;
        }
        //https://stackoverflow.com/questions/20511347/a-good-hash-function-for-a-vector
        std::size_t HashVector(const std::vector<unsigned int>& vec) const {
            std::size_t seed = vec.size();
            for (auto& i : vec) {
                seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            }
            return seed;
        }
    };
};

class Walker {
public:
    unsigned int totalActions = 0;
    Walker(PDDLInstance* instance, ActionGenerator actionGenerator, BaseHeuristics<PDDLActionInstance, PDDLContext> *heuristic, BaseDepthFunction *depthFunc) : 
    instance(instance), actionGenerator(actionGenerator), heuristic(heuristic), depthFunc(depthFunc) {}
    Path Walk();
    Path Walk(PDDLState state);
    static void DoAction(PDDLState *state, const PDDLActionInstance *action);
private:
    PDDLInstance* instance;
    ActionGenerator actionGenerator;
    BaseHeuristics<PDDLActionInstance, PDDLContext> *heuristic;
    BaseDepthFunction *depthFunc;

    
};

#endif
