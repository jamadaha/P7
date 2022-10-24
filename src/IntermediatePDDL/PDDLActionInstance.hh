#ifndef PDDL_ACTION_INSTANCE_HH
#define PDDL_ACTION_INSTANCE_HH

#include <vector>
#include <string>

#include "PDDLAction.hh"

struct PDDLInstance;

class PDDLActionInstance {
public:
    const PDDLAction *action;
    const std::vector<unsigned int> objects;
    PDDLActionInstance(const PDDLAction *action, const std::vector<unsigned int> objects) : action(action), objects(objects) {}; 
    std::string ToString(const PDDLInstance* instance);
    std::string LiteralsToString(std::vector<PDDLLiteral> literals, const PDDLInstance* instance);
private:
};

#endif
