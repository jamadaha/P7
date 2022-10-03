#ifndef PDDL_DOMAIN
#define PDDL_DOMAIN

#include <vector>
#include <string>
#include <unordered_map>
#include <map>

#include "../PDDLParser/domain.hh"

struct PDDLType {
    std::string name;
    PDDLType(std::string name) : name(name) {};
};

struct PDDLArg {
    std::string name;
    PDDLType* typeRef;
    PDDLArg(std::string name, PDDLType* typeRef) : name(name), typeRef(typeRef) {};
};

struct PDDLPredicate {
    std::string name;
    std::vector<PDDLArg> args;
    PDDLPredicate(std::string name, std::vector<PDDLArg> args) : name(name), args(args) {};
};

struct PDDLBoolPredicate {
    PDDLPredicate predicate;
    bool state;
    PDDLBoolPredicate(PDDLPredicate predicate, bool state) : predicate(predicate), state(state) {};
};

struct PDDLAction {
    std::string name;
    std::vector<PDDLArg> parameters;
    std::vector<PDDLBoolPredicate> preconditions;
    std::vector<PDDLBoolPredicate> effects;
};

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
        for (auto const& predicate : *domain->_predicates)
            predicates.push_back(PDDLPredicate(predicate->_name,  GetArguments(predicate->_args, predicate->_types)));

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

private:
    std::vector<PDDLArg> GetArguments(const StringList* params, const TypeDict* types) {
        std::vector<PDDLArg> args;
        std::unordered_map<std::string, std::string> tempTypeDict;
            // Get types
            if (types != nullptr) {
                for (auto const& [x, y] : *types) {
                    // Check if type already exists
                    if (typeDict.find(y) == typeDict.end())
                        typeDict.emplace(y, new PDDLType(y));
                    tempTypeDict.emplace(x, y);
                    //predicate.predicate.push_back(PDDLArg(x, typeDict[y]));
                }
            }

            for (auto const& arg : *params) {
                if (tempTypeDict.find(arg) == tempTypeDict.end())
                    args.push_back(PDDLArg(arg, nullptr));
                else
                    args.push_back(PDDLArg(arg, typeDict[tempTypeDict[arg]]));
            }
        return args;
    }
    
    std::vector<PDDLBoolPredicate> GetLogicalExpressions(const std::vector<std::pair<Predicate*,bool>*> *logExp) {
        std::vector<PDDLBoolPredicate> predicates;
        for (auto const& exp : *logExp) {
            std::vector<PDDLArg> args = GetArguments(exp->first->_args, exp->first->_types);
            predicates.push_back(PDDLBoolPredicate(PDDLPredicate(exp->first->_name, args), exp->second));
        }
        return predicates;
    }
};

#endif
