#ifndef MACRO
#define MACRO

#include <vector>
#include <unordered_map>

#include "GroundedAction.hh"
#include "../IntermediatePDDL/PDDLInstance.hh"

class Macro {
public:
    const std::string name;
    const GroundedAction groundedAction;
    const std::vector<PDDLActionInstance> path;
    Macro(GroundedAction groundedAction, std::vector<PDDLActionInstance> path) :
        groundedAction(groundedAction), path(path), name("macro-" + groundedAction.name) {};
private:
    
};

#endif
