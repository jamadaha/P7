#ifndef MACRO
#define MACRO

#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "GroundedAction.hh"
#include "../IntermediatePDDL/PDDLInstance.hh"

class Macro {
public:
    const std::string name;
    const GroundedAction groundedAction;
    const std::vector<std::vector<PDDLActionInstance*>> paths;
    Macro(GroundedAction groundedAction, std::vector<std::vector<PDDLActionInstance*>> paths) :
        groundedAction(groundedAction), paths(paths), name("macro-" + groundedAction.name) {};
private:
    
};

#endif
