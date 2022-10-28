#ifndef INSTANCE_GENERATOR
#define INSTANCE_GENERATOR

#include <vector>
#include <set>

#include "../IntermediatePDDL/PDDLInstance.hh"
#include "Macro.hh"

class InstanceGenerator{
public:
    static PDDLInstance GenerateInstance(const PDDLDomain *domain, const PDDLProblem *problem, const std::vector<Macro> *macros);
private:
    static std::vector<PDDLLiteral> GenerateLiterals(const std::unordered_map<GroundedLiteral, bool> *macroPreconditions, 
    std::unordered_map<unsigned int, unsigned int> *groundedToIndex);

};

#endif
