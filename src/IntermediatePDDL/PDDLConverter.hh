#ifndef PDDL_CONVERTER
#define PDDL_CONVERTER

#include <vector>
#include <string>
#include <unordered_map>

#include "PDDLPredicate.hh"
#include "PDDLAction.hh"
#include "PDDLDomain.hh"
#include "PDDLProblem.hh"
#include "../PDDLParser/domain.hh"
#include "../PDDLParser/problem.hh"
#include "../Helpers/StringHelper.hh"

class PDDLConverter {
public:
    static PDDLDomain Convert(Domain *domain);
    static PDDLProblem Convert(PDDLDomain *domain, Problem *problem);

private:
    static std::vector<PDDLLiteral> GetLiteralList(std::unordered_map<std::string, unsigned int> predicateMap, std::unordered_map<std::string, unsigned int> parameterIndex, const std::vector<std::pair<Predicate*,bool>*>* input);
    static PDDLAction GenerateAction(std::string name, const StringList *parameters, const PreconditionList *preconditions, const EffectList *effects, std::unordered_map<std::string, unsigned int> predicateMap);
    static std::unordered_map<unsigned int, std::unordered_set<unsigned int>> GetUnaryFacts(PDDLDomain *domain, std::unordered_map<std::string, unsigned int> *objectMap, LiteralList *literalList);
    static std::unordered_map<unsigned int, std::unordered_set<std::pair<unsigned int, unsigned int>>> GetBinaryFacts(PDDLDomain *domain, std::unordered_map<std::string, unsigned int> *objectMap, LiteralList *literalList);
    static std::unordered_map<unsigned int, std::unordered_set<MultiFact>> GetMultiFacts(PDDLDomain *domain, std::unordered_map<std::string, unsigned int> *objectMap, LiteralList *literalList);
};

#endif
