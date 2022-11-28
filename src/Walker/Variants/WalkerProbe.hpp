#ifndef WALKER_PROBE
#define WALKER_PROBE

#include <vector>
#include <list>

#include "../../PDDL/ActionInstance.hh"
#include "../Heuristics/BaseHeuristic.hh"
#include "../DepthFunctions/BaseDepthFunction.hh"
#include "../WidthFunctions/BaseWidthFunction.hh"
#include "../ActionGenerator.hpp"

#include "../../Config/Config.hh"
#include "../../Helpers/Hashes.hh"

#include "../BaseWalker.hh"

class WalkerProbe : public BaseWalker {
public:
    WalkerProbe(PDDL::Instance* instance, BaseHeuristic* heuristic, BaseWidthFunction* widthFunc)
        : BaseWalker("Default", instance, heuristic, widthFunc) {}
    std::vector<Path> Walk() override;
private:
    const unsigned int maxStepCount = 1000;
    Path Walk(BaseHeuristic* heuristic, const PDDL::State* state, unsigned int* current);

    template <typename T>
    std::unordered_map<unsigned int, T> GetFactSubset(std::unordered_map<unsigned int, T>* initSource, std::unordered_map<unsigned int, T>* goalSource);
};

#endif
