#ifndef PDDL_DOMAIN
#define PDDL_DOMAIN

#include <vector>
#include <string>

struct PDDLType {
    const std::string name;
};

struct PDDLTypeRef {
    const std::string name;
    const PDDLType* type;
};

struct PDDLPredicate {
    const std::vector<PDDLTypeRef> predicate;
};

struct PDDLREMember {
    const PDDLPredicate* type;
    const bool state;
};

struct PDDLRE {
    const std::vector<PDDLREMember> valueList;
};

struct PDDLAction {
    const std::string name;
    const std::vector<PDDLTypeRef> parameters;
    const std::vector<PDDLRE> preconditions;
    const std::vector<PDDLRE> effects;
};

class PDDLDomain {
public:
    const std::vector<std::string> requirements;
    const std::vector<PDDLPredicate> predicates;
    const std::vector<PDDLAction> actions;

private:

};

#endif
