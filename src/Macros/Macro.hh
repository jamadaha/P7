#ifndef MACRO
#define MACRO

#include <vector>

#include "GroundedAction.hh"
#include "../PDDL/Instance.hh"

namespace Macros {
    class Macro {
    public:
        const std::string name;
        const GroundedAction groundedAction;
        const std::vector<PDDL::ActionInstance> path;
        Macro(GroundedAction groundedAction, std::vector<PDDL::ActionInstance> path) :
            groundedAction(groundedAction), path(path), name("MACRO-" + groundedAction.name) {};
    };
}

#endif
