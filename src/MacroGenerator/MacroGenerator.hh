#ifndef MACRO_GENERATOR
#define MACRO_GENERATOR

#include <vector>
#include <unordered_map>

#include "Macro.hh"
#include "GroundedAction.hh"
#include "../IntermediatePDDL/PDDLInstance.hh"

class MacroGenerator {
public:
    static Macro GenerateMacro(const std::vector<PDDLActionInstance*> *actions);


private:
    static std::vector<PDDLActionInstance> CloneOriginalPath(const std::vector<PDDLActionInstance*> *actions);
    static std::vector<GroundedAction> GroundActions(const std::vector<PDDLActionInstance*> *actions);
    static GroundedAction CombineActions(const std::vector<GroundedAction> *actions);
    static std::unordered_map<GroundedLiteral, bool> CombinePreconditions(
        std::unordered_map<GroundedLiteral, bool> priorPrecon, 
        std::unordered_map<GroundedLiteral, bool> latterPrecon,
        std::unordered_map<GroundedLiteral, bool> priorEffs);
    static std::unordered_map<GroundedLiteral, bool> CombineEffects(
        std::unordered_map<GroundedLiteral, bool> priorEffects, 
        std::unordered_map<GroundedLiteral, bool> latterEffects);
    static std::unordered_set<unsigned int> GenerateParameters(
        std::unordered_map<GroundedLiteral, bool> preconditions, 
        std::unordered_map<GroundedLiteral, bool> effects);
};

#endif
