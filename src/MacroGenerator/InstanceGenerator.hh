#ifndef INSTANCE_GENERATOR
#define INSTANCE_GENERATOR

#include <vector>
#include <set>

#include "../PDDL/Instance.hh"
#include "Macro.hh"

class InstanceGenerator{
public:
    static PDDL::Instance GenerateInstance(const PDDL::Domain *domain, const PDDL::Problem *problem, const std::vector<Macro> *macros);
private:
    static std::vector<PDDL::Literal> GenerateLiterals(const std::unordered_map<GroundedLiteral, bool> *macroPreconditions,
    std::unordered_map<unsigned int, unsigned int> *groundedToIndex);
    static void AppendObjectPreconditions(std::vector<PDDL::Literal> *literals,
const std::unordered_map<std::string, unsigned int> predicateMap, 
const std::vector<std::string> parameters);

};

#endif
