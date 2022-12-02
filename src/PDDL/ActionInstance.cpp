#include "ActionInstance.hh"
#include "Instance.hh"

using namespace std;
using namespace PDDL;

#ifndef NDEBUG
void ActionInstance::SetupDebugInfo() {
    for (int i = 0; i < objects.size(); i++)
        objectsName.push_back(PDDL::CurrentInstance->problem->objects.at(i));
}
#endif

string ActionInstance::ToString(const Instance* instance)
{
    //Print action
    string temp = action->name + "(";
    for (int i = 0; i < objects.size(); i++)
    {
        temp += instance->problem->objects[objects[i]];
        if (i + 1 < objects.size()) 
        {
            temp += " ";
        }
    }
    temp += ")\n";

    temp += "precondition(" + LiteralsToString(action->preconditions, instance);
    temp += "effect(" + LiteralsToString(action->effects, instance);

    return temp;
}

string ActionInstance::LiteralsToString(vector<Literal> literals, const Instance* instance)
{
    string temp;
    for (int i = 0; i < literals.size(); i++)
    {
        temp += "(";
        Literal literal = literals[i];

        if (!literal.value) {
            temp += "not ";
        }
        auto predicate = instance->domain->predicates[literal.predicateIndex];
        temp += predicate.name + " ";

        for (int i = 0; i < literal.args.size(); i++)
        {
            temp += instance->problem->objects[objects[literal.args[i]]];
            if (i + 1 < literal.args.size()) 
            {
                temp += " ";
            }
        }
        temp += ")";

        if (i + 1 < literals.size()) 
        {
            temp += " ";
        }
    }
    temp += ")\n";
    return temp;
}

size_t ActionInstance::GetHash() {
    if (Hash != 0)
        return Hash;
    Hash = hash<ActionInstance>{}(*this);
    return Hash;
}