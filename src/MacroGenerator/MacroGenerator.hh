#ifndef MACRO_GENERATOR
#define MACRO_GENERATOR

#include <vector>
#include <unordered_map>

#include "Macro.hh"
#include "GroundedAction.hh"
#include "../IntermediatePDDL/PDDLInstance.hh"
#include "../EntanglementFinder/MacroCandidate.hh"

class MacroGenerator {
public:
    MacroGenerator() : domain(nullptr), problem(nullptr) {};
    MacroGenerator(const PDDLDomain *domain, const PDDLProblem *problem) : domain(domain), problem(problem) {};
    Macro GenerateMacro(const MacroCandidate* candidate);


private:
    const PDDLDomain *domain;
    const PDDLProblem *problem;
    std::unordered_map<unsigned int, bool> partials;

    unsigned int groundedActionsCount = 0;
    unsigned int macroCount = 0;

    Macro GeneratePartiallyGroundedMacro(const MacroCandidate* candidate);
    Macro GenerateGroundedMacro(const MacroCandidate* candidate);

    std::vector<PDDLActionInstance> CloneOriginalPath(const std::vector<PDDLActionInstance*> *actions);
    std::vector<GroundedAction> GroundActions(const std::vector<PDDLActionInstance*>* actions);
    std::unordered_map<unsigned int, bool> FindPartialPreconditions(const std::vector < std::vector<PDDLActionInstance*>>* actions);
    std::unordered_map<unsigned int, bool> GenerateStaticList(const std::vector < std::vector<PDDLActionInstance*>>* actions);
    GroundedAction CombineActions(const std::vector<GroundedAction> *actions);
    std::unordered_map<GroundedLiteral, bool> CombinePreconditions(
        std::unordered_map<GroundedLiteral, bool> priorPrecon, 
        std::unordered_map<GroundedLiteral, bool> latterPrecon,
        std::unordered_map<GroundedLiteral, bool> priorEffs);
    std::unordered_map<GroundedLiteral, bool> CombineEffects(
        std::unordered_map<GroundedLiteral, bool> priorEffects, 
        std::unordered_map<GroundedLiteral, bool> latterEffects);
    std::unordered_set<unsigned int> GenerateParameters(
        std::unordered_map<GroundedLiteral, bool> preconditions, 
        std::unordered_map<GroundedLiteral, bool> effects);
};

#endif
