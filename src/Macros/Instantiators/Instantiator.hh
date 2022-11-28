#ifndef INSTANCE_GENERATOR
#define INSTANCE_GENERATOR

#include <vector>
#include <set>

#include "../PDDL/Instance.hh"
#include "../Macro.hh"

namespace Macros {
    class Instantiator {
    public:
        static PDDL::Instance GenerateInstance(const PDDL::Domain* domain, const PDDL::Problem* problem, const std::vector<Macro>* macros);
    private:
        static std::vector<PDDL::Literal> GenerateLiterals(
            const std::unordered_map<GroundedLiteral, bool>* macroPreconditions,
            std::unordered_map<unsigned int, unsigned int>* groundedToIndex);
        static void GenerateUnaryFacts(
            const std::vector<Macro>* macros,
            const PDDL::Problem* problem,
            std::unordered_map<std::string, unsigned int>* predicateMap,
            std::unordered_map<unsigned int, std::unordered_set<unsigned int>>* unaryFacts,
            std::vector<PDDL::Predicate>* predicates);
        static void GenerateMacroActions(
            const std::vector<Macro>* macros,
            const PDDL::Problem* problem,
            const std::unordered_map<std::string, unsigned int>* predicateMap,
            std::vector<PDDL::Action>* actions);
        static void AppendObjectPreconditions(
            std::vector<PDDL::Literal>* literals,
            const std::unordered_map<std::string, unsigned int>* predicateMap,
            const std::vector<std::string>* parameters);
    };
}

#endif
