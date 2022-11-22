#ifndef UNARY_FACT_VERIFIER
#define UNARY_FACT_VERIFIER

#include <unordered_set>

#include "../../IntermediatePDDL/PDDLAction.hh"
#include "../../IntermediatePDDL/PDDLState.hh"

#include "../../Helpers/AlgorithmHelper.hh"

class UnaryFactVerifier {
public:
    UnaryFactVerifier(unsigned int objectCount) : objects(GenerateObjects(objectCount)) {};

    std::vector<std::unordered_set<unsigned int>> GetLegalObjects(const PDDLAction *action, const PDDLState *state) const;

private:
    const std::unordered_set<unsigned int> objects;

    std::unordered_set<unsigned int> GetLegalObjectsForParameter(   const std::unordered_set<const PDDLLiteral*> *literals, 
                                                                    const PDDLState *state) const;
    static void RemoveIllegal( std::unordered_set<unsigned int> &set, 
                        const std::unordered_set<const PDDLLiteral*> *literals, 
                        const PDDLState *state);

    static std::unordered_set<unsigned int> GenerateObjects(unsigned int objectCount) {
        std::unordered_set<unsigned int> tempObjects;
        for (unsigned int i = 0; i < objectCount; i++)
            tempObjects.emplace(i);
        return tempObjects;
    }
};

#endif