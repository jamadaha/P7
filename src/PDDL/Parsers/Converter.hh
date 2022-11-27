#ifndef PDDL_CONVERTER
#define PDDL_CONVERTER

#include <vector>
#include <string>
#include <unordered_map>

#include "../Predicate.hh"
#include "../Action.hh"
#include "../Domain.hh"
#include "../Problem.hh"
#include "ExternalParser/domain.hh"
#include "ExternalParser/problem.hh"
#include "../Helpers/StringHelper.hh"

class Converter {
public:
    static PDDL::Domain Convert(Domain* domain);
    static PDDL::Problem Convert(PDDL::Domain* domain, Problem* problem);

private:
    static std::vector<PDDL::Literal> GetLiteralList(
        std::unordered_map<std::string, unsigned int> predicateMap,
        std::unordered_map<std::string, unsigned int> parameterIndex,
        const std::vector<std::pair<Predicate*, bool>*>* input);
    static PDDL::Action GenerateAction(
        std::string name,
        const StringList* parameters,
        const PreconditionList* preconditions,
        const EffectList* effects,
        std::unordered_map<std::string, unsigned int> predicateMap);
    static std::unordered_map<unsigned int, std::unordered_set<unsigned int>> GetUnaryFacts(
        PDDL::Domain* domain,
        std::unordered_map<std::string, unsigned int>* objectMap,
        LiteralList* literalList);
    static std::unordered_map<unsigned int, std::unordered_set<std::pair<unsigned int, unsigned int>>> GetBinaryFacts(
        PDDL::Domain* domain,
        std::unordered_map<std::string, unsigned int>* objectMap,
        LiteralList* literalList);
};

#endif
