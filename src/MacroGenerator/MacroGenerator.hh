#ifndef MACRO_GENERATOR
#define MACRO_GENERATOR

#include <vector>
#include <unordered_map>

#include "Macro.hh"
#include "GroundedAction.hh"
#include "../IntermediatePDDL/PDDLInstance.hh"

class MacroGenerator {
public:
    MacroGenerator(){};
    MacroGenerator(PDDLDomain *domain) : domain(domain) {};
    Macro GenerateMacro(const std::vector<PDDLActionInstance> *actions);


private:
    const PDDLDomain *domain = nullptr;
    unsigned int macroCount = 0;

    std::vector<PDDLActionInstance> CloneOriginalPath(const std::vector<PDDLActionInstance> *actions);
    std::vector<GroundedAction> GroundActions(const std::vector<PDDLActionInstance> *actions);
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
