#ifndef INSTANCE_GENERATOR
#define INSTANCE_GENERATOR

#include <vector>
#include <set>
#include <string>

#include "../IntermediatePDDL/PDDLInstance.hh"
#include "Macro.hh"

class InstanceGenerator{
public:
    static PDDLInstance GenerateInstance(const PDDLDomain *domain, const PDDLProblem *problem, const std::vector<Macro> *macros);
private:
    static std::vector<PDDLLiteral> GenerateLiterals(const std::unordered_map<GroundedLiteral, bool> *macroPreconditions, 
    std::unordered_map<unsigned int, unsigned int> *groundedToIndex);
    static void AppendObjectPreconditions(std::vector<PDDLLiteral> *literals, 
const std::unordered_map<std::string, unsigned int> predicateMap, 
const std::vector<std::string> parameters);

};

#endif
