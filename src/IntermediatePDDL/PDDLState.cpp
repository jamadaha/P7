#include "PDDLState.hh"

#include "PDDLInstance.hh"

std::string PDDLState::ToString(const PDDLInstance* instance)
{
    std::string temp = "State ";
    for (auto unaryFact : unaryFacts)
    {
        if (unaryFact.second.size() > 0) {
            temp += "(";
            temp += instance->domain->predicates[unaryFact.first].name;

            for (auto objectindex : unaryFact.second) {
                temp += " " + instance->problem->objects[objectindex];
            }
            temp += ")";
        }
        

    }

    for (auto multiFact : multiFacts) {
        for (auto facts : multiFact.second) {
            temp += "(";
            temp += instance->domain->predicates[multiFact.first].name;
            for (auto fact : facts.fact) {
                
                temp += " " + instance->problem->objects[fact];
               
            }
            temp += ")";
        }
    }

    temp += "\n";
    return temp;
};
