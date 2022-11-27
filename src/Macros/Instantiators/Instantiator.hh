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
    static std::vector<PDDLLiteral> GenerateLiterals(
        const std::unordered_map<GroundedLiteral, bool> *macroPreconditions, 
        std::unordered_map<unsigned int, unsigned int> *groundedToIndex);
    static void GenerateUnaryFacts(
        const std::vector<Macro>* macros,
        const PDDLProblem* problem,
        std::unordered_map<std::string, unsigned int>* predicateMap,
        std::unordered_map<unsigned int, std::unordered_set<unsigned int>>* unaryFacts,
        std::vector<PDDLPredicate>* predicates);
    static void GenerateMacroActions(
        const std::vector<Macro>* macros,
        const PDDLProblem* problem,
        const std::unordered_map<std::string, unsigned int>* predicateMap,
        std::vector<PDDLAction>* actions);
    static void AppendObjectPreconditions(
        std::vector<PDDLLiteral> *literals, 
        const std::unordered_map<std::string, unsigned int>* predicateMap, 
        const std::vector<std::string>* parameters);

};

#endif
