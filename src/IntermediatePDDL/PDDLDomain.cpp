#include "PDDLDomain.hh"

using namespace std;

vector<PDDLArg> PDDLDomain::GetArguments(const StringList* params, const TypeDict* types) {
    vector<PDDLArg> args;
    unordered_map<string, string> tempTypeDict;
    // Get types
    if (types != nullptr) {
        for (auto const& [x, y] : *types) {
            tempTypeDict.emplace(x, y);
        }
    }

    for (int i = 0; i < params->size(); i++) {
        auto p = (*params)[i];
        if (tempTypeDict.find((*params)[i]) == tempTypeDict.end())
            args.push_back(PDDLArg((*params)[i], nullptr));
        else
            args.push_back(PDDLArg((*params)[i], typeDict[tempTypeDict[(*params)[i]]]));
    }
    return args;
}

std::vector<PDDLArg*> PDDLDomain::GetActionParameterRef(std::vector<PDDLArg> args, std::vector<PDDLArg> *params) {
    std::vector<PDDLArg*> refArg;
    for (int i = 0; i < args.size(); i++)
        for (int t = 0; t < params->size(); t++)
            if ((*params)[t].name == args[i].name) {
                refArg.push_back(&(*params)[t]);
                break;
            }
    return refArg;
}

PDDLPredicate* PDDLDomain::GetPredicate(std::string name) {
    for (int i = 0; i < this->predicates.size(); i++)
        if (this->predicates[i].name == name)
            return (&(this->predicates[i]));
    return nullptr;
}

void PDDLDomain::AddTypes(const TypeDict* types) {
    if (types != nullptr) {
        for (auto const& [x, y] : *types) {
            // Check if type already exists
            if (typeDict.find(y) == typeDict.end())
                typeDict.emplace(y, new PDDLType(y));
        }
    }
}

vector<PDDLLiteral> PDDLDomain::GetLogicalExpressions(const vector<pair<Predicate*, bool>*>* logExp, std::vector<PDDLArg> *params) {
    vector<PDDLLiteral> predicates;
    for (auto const& exp : *logExp) {
        vector<PDDLArg> args = GetArguments(exp->first->_args, exp->first->_types);
        predicates.push_back(PDDLLiteral(
            GetPredicate(exp->first->_name),
            GetActionParameterRef(args, params),
            exp->second
        ));
    }
    return predicates;
}
