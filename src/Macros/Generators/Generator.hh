#ifndef MACRO_GENERATOR
#define MACRO_GENERATOR

#include <vector>
#include <unordered_map>

#include "../Macro.hh"
#include "../GroundedAction.hh"
#include "../PDDL/Instance.hh"

namespace Macros {
    class Generator {
    public:
        Generator() {};
        Generator(PDDL::Domain* domain) : domain(domain) {};
        Macro GenerateMacro(std::vector<PDDL::ActionInstance>* actions);


    private:
        const PDDL::Domain* domain = nullptr;
        unsigned int macroCount = 0;

        std::vector<GroundedAction> GroundActions(std::vector<PDDL::ActionInstance>* actions);
        GroundedAction GroundAction(PDDL::ActionInstance* action);
        std::vector<unsigned int> GetGroundedArguments(PDDL::ActionInstance* action, std::vector<unsigned int> args);
        GroundedAction CombineActions(const std::vector<GroundedAction>* actions);
        void CombinePreconditions(
            std::unordered_map<GroundedLiteral, bool>* priorPrecon,
            std::unordered_map<GroundedLiteral, bool> latterPrecon,
            std::unordered_map<GroundedLiteral, bool>* priorEffs);
        void CombineEffects(
            std::unordered_map<GroundedLiteral, bool>* priorEffects,
            std::unordered_map<GroundedLiteral, bool> latterEffects);
        std::unordered_set<unsigned int> GenerateParameters(
            std::unordered_map<GroundedLiteral, bool>* preconditions,
            std::unordered_map<GroundedLiteral, bool>* effects);
    };
}

#endif
