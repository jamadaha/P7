#ifndef PDDL_ACTION_INSTANCE_HH
#define PDDL_ACTION_INSTANCE_HH

#include <vector>
#include <string>

#include "PDDLAction.hh"

#include "PDDLDomain.hh"

class PDDLActionInstance {
public:
    const PDDLAction *action;
    const std::vector<unsigned int> objects;
    PDDLActionInstance(const PDDLAction *action, const std::vector<unsigned int> objects) : action(action), objects(objects) {}; 
    std::string ToString(std::vector<std::string> objectnames, PDDLDomain* domain) {

        //Print action
        std::string temp = action->name + "(";
        for (int i = 0; i < objects.size(); i++)
        {
            temp += objectnames[objects[i]];
            if (i + 1 < objects.size()) {
                temp += " ";
            }
        }
        temp += ")\n";

        //Print precondition
        temp += "precondition(";
        for (int i = 0; i < action->preconditions.size(); i++)
        {
            temp += "(";
            PDDLLiteral literal = action->preconditions[i];
            
            if (!literal.value) {
                temp += "not ";
            }
            auto predicate = domain->predicates[literal.predicateIndex];
            temp += predicate.name + " ";
            //temp += objectnames[literal.predicateIndex] + " ";

            for (int i = 0; i < literal.args.size(); i++)
            {
                temp += objectnames[literal.args[i]];
                if (i + 1 < literal.args.size()) {
                    temp += " ";
                }
            }
            
            
            temp += ")";

            if (i + 1 < action->preconditions.size()) {
                temp += " ";
            }
            
        }
        temp += ")\n";

        //Print effect
        return temp;
    };
private:
};

#endif
