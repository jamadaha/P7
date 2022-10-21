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
    std::string ToString(std::vector<std::string> objectnames) {
        std::string temp = action->name + "(";
        for (int i = 0; i < objects.size(); i++)
        {
            temp += objectnames[objects[i]];
            if (i + 1 < objects.size()) {
                temp += " ";
            }
        }
        temp += ")\n";
        return temp;
    };
private:
};

#endif
