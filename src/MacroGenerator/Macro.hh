#ifndef MACRO
#define MACRO

#include <vector>

#include "GroundedAction.hh"
#include "../IntermediatePDDL/PDDLInstance.hh"

class Macro {
public:
    const GroundedAction groundedAction;
    const std::vector<PDDLActionInstance*> path;
    Macro(GroundedAction groundedAction, std::vector<PDDLActionInstance*> path) : 
        groundedAction(groundedAction), path(path) {};
private:
    
};

#endif
