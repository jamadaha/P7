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
    const std::unordered_map<unsigned int, bool> Partials;
    Macro(GroundedAction groundedAction, std::vector<PDDLActionInstance> path, std::unordered_map<unsigned int, bool> partials) :
        groundedAction(groundedAction), path(path), Partials(partials), name("macro-" + groundedAction.name) {};
private:
    
};

#endif
