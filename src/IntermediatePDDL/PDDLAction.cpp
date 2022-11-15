#include "PDDLAction.hh"

#include "../Helpers/AlgorithmHelper.hh"

std::vector<std::unordered_set<const PDDLLiteral*>> PDDLAction::GenerateApplicableLiterals(bool unary) const {
    std::vector<std::unordered_set<const PDDLLiteral*>> set;
    if (parameters.size() == 0 || preconditions.size() == 0)
        return set;
    for (int i = 0; i < parameters.size(); i++) {
        std::unordered_set<const PDDLLiteral*> tempSet;
        for (int literalIndex = 0; literalIndex < preconditions.size(); literalIndex++) {
            const PDDLLiteral *literal = &preconditions.at(literalIndex);
            if (unary ? (literal->args.size() != 1) : (literal->args.size() == 1))
                continue;
            for (int argIndex = 0; argIndex < literal->args.size(); argIndex++)
                if (i == literal->args.at(argIndex))
                    tempSet.emplace(literal);
        }
        set.push_back(tempSet);
    }
    return set;
};

std::vector<std::unordered_set<unsigned int>> PDDLAction::GenerateApplicablePredicates() const {
    std::vector<std::unordered_set<unsigned int>> set;
    for (int i = 0; i < parameters.size(); i++) {
        std::unordered_set<unsigned int> tempSet;
        
        for (auto literal : applicableUnaryLiterals.at(i)) {
            tempSet.emplace(literal->predicateIndex);
        }
        set.push_back(tempSet);
    }
    return set;
};

std::unordered_set<std::unordered_set<unsigned int>> PDDLAction::GenerateClusters(const std::vector<PDDLLiteral> *literals) const {
    std::unordered_map<unsigned int, std::unordered_set<unsigned int>> relatedParameters;

    for (int i = 0; i < literals->size(); i++) {
        auto literal = &literals->at(i);

        if (literal->args.size() == 1)
            continue;

        std::unordered_set<unsigned int> tempCluster;

        for (int t = 0; t < literal->args.size(); t++) {
            auto arg = literal->args.at(t);
            tempCluster.emplace(arg);
        }

        for (auto iter = tempCluster.begin(); iter != tempCluster.end(); iter++)
            for (auto iter2 = tempCluster.begin(); iter2 != tempCluster.end(); iter2++) {
                if (iter == iter2)
                    continue;
                
                if (!relatedParameters.contains(*iter))
                    relatedParameters[*iter] = { *iter2 };
                else
                    relatedParameters.at(*iter).emplace(*iter2);
            }

    }

    std::unordered_set<std::unordered_set<unsigned int>> clusters;
    std::unordered_set<unsigned int> handledParameters;

    for (auto iter = relatedParameters.begin(); iter != relatedParameters.end(); iter++) {
        auto param = (*iter).first;

        if (handledParameters.contains(param))
            continue;

        std::unordered_set<unsigned int> tempCluster{ param };
        unsigned int priorSize; 
        do {
            priorSize = tempCluster.size();
            for (auto clusterIter = tempCluster.begin(); clusterIter != tempCluster.end(); clusterIter++) {
                if (!handledParameters.contains(*clusterIter)) {
                    AlgorithmHelper::InsertAll(tempCluster, relatedParameters.at(*clusterIter));
                    handledParameters.emplace(*clusterIter);
                }
            }
        } while (priorSize != tempCluster.size());
        
        clusters.emplace(tempCluster);
    }

    return clusters;
}
