#ifndef ACTION_GENERATOR
#define ACTION_GENERATOR

#include <vector>
#include <string>
#include <map>
#include <set>
#include <iterator>

#include "../IntermediatePDDL/PDDLActionInstance.hh"
#include "../IntermediatePDDL/PDDLInstance.hh"

class ActionGenerator {
public:
    ActionGenerator(PDDLDomain* domain) : domain(domain) {};
    std::vector<PDDLActionInstance> GenerateActions(const PDDLState *state);
private:
    PDDLDomain* domain;
     // Given some action generate all legal parameter variations
    std::vector<PDDLActionInstance> GenerateLegal(const PDDLAction *action, const PDDLState *state);
    std::unordered_set<unsigned int> GetCandidateObjects(std::unordered_set<const PDDLLiteral*> literals, const PDDLState *state);
    bool IsLegal(const std::vector<PDDLLiteral> *literals, const PDDLState *state, std::vector<unsigned int> *objects);
    bool Iterate(std::vector<std::unordered_set<unsigned int>::iterator> *iteration, std::vector<std::unordered_set<unsigned int>> *candidateObjects);
};

#endif
