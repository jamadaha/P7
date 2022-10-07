#ifndef PDDL_ACTION_INSTANCE
#define PDDL_ACTION_INSTANCE

#include <vector>
#include <string>

#include "PDDLAction.hpp"

class PDDLActionInstance {
public:
    PDDLAction action;
    std::vector<std::string> arguments;
    PDDLActionInstance(PDDLAction action, std::vector<std::string> arguments) : action(action), arguments(arguments) {};
private:
};

#endif
