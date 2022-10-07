#ifndef PDDL_DOMAIN
#define PDDL_DOMAIN

#include <vector>
#include <string>
#include <unordered_map>
#include <map>

#include "PDDLType.hpp"
#include "PDDLArg.hpp"
#include "PDDLPredicate.hpp"
#include "PDDLLiteral.hpp"
#include "PDDLAction.hpp"

#include "../PDDLParser/domain.hh"

class PDDLDomain {
public:
    std::string name;
    std::unordered_map<std::string, PDDLType*> typeDict;
    std::vector<std::string> requirements;
    std::vector<PDDLPredicate> predicates;
    std::vector<PDDLAction> actions;

    PDDLDomain(Domain* domain) {
        name = domain->_name.c_str();
        // Get Requirements
        for (int i = 0; i < domain->_requirements->size(); i++)
            requirements.push_back((*domain->_requirements)[i]);

        // Get Predicates
        for (auto const& predicate : *domain->_predicates) {
            AddTypes(predicate->_types);
            predicates.push_back(PDDLPredicate(predicate->_name,  GetArguments(predicate->_args, predicate->_types)));
        }
            

        // Get Actions
        for (auto const& action : *domain->_actions) {
            PDDLAction newAction = PDDLAction();
            newAction.name = action->_name;
            newAction.parameters = GetArguments(action->_params, action->_types);
            newAction.preconditions = GetLogicalExpressions(action->_precond);
            newAction.effects = GetLogicalExpressions(action->_effects);
            actions.push_back(newAction);
        }
    };

    PDDLDomain(PDDLDomain* domain) {
        
    }

    std::vector<PDDLArg> GetArguments(const StringList* params, const TypeDict* types) {
        std::vector<PDDLArg> args;
        std::unordered_map<std::string, std::string> tempTypeDict;
            // Get types
            if (types != nullptr) {
                for (auto const& [x, y] : *types) {
                    tempTypeDict.emplace(x, y);
                }
            }

            for (int i = 0; i < params->size(); i++) {
                if (tempTypeDict.find((*params)[i]) == tempTypeDict.end())
                    args.push_back(PDDLArg(i, (*params)[i], nullptr));
                else
                    args.push_back(PDDLArg(i, (*params)[i], typeDict[tempTypeDict[(*params)[i]]]));
            }
        return args;
    }

private:
    void AddTypes(const TypeDict* types) {
        if (types != nullptr) {
            for (auto const& [x, y] : *types) {
                // Check if type already exists
                if (typeDict.find(y) == typeDict.end())
                    typeDict.emplace(y, new PDDLType(y));
            }
        }
    }
    
    std::vector<PDDLLiteral> GetLogicalExpressions(const std::vector<std::pair<Predicate*,bool>*> *logExp) {
        std::vector<PDDLLiteral> predicates;
        for (auto const& exp : *logExp) {
            std::vector<PDDLArg> args = GetArguments(exp->first->_args, exp->first->_types);
            predicates.push_back(PDDLLiteral(PDDLPredicate(exp->first->_name, args), exp->second));
        }
        return predicates;
    }
};

#endif
