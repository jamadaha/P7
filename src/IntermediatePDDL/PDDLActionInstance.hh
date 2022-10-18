#ifndef PDDL_ACTION_INSTANCE_HH
#define PDDL_ACTION_INSTANCE_HH

#include <vector>
#include <string>

#include "PDDLAction.hh"

class PDDLActionInstance {
public:
    const PDDLAction *action;
    const std::vector<unsigned int> objects;
    PDDLActionInstance(const PDDLAction *action, const std::vector<unsigned int> objects) : action(action), objects(objects) {}; 
private:
};

#endif
