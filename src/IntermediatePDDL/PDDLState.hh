#ifndef PDDL_STATE_HH
#define PDDL_STATE_HH

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include "PDDLActionInstance.hh"

struct MultiFact {
    std::vector<unsigned int> fact;
    MultiFact(std::vector<unsigned int> fact) : fact(fact) {};
    friend bool operator== (const MultiFact &lhs, const MultiFact &rhs) {
        size_t lhsSize = lhs.fact.size();
        if (lhsSize != rhs.fact.size())
            return false;
        for (int i = 0; i < lhsSize; i++)
            if (lhs.fact.at(i) != rhs.fact.at(i))
                return false;
        return true;
    }
};

struct PDDLState {
    // Key - Index of predicate | Value - Set of objects which the predicate is true for
    std::unordered_map<unsigned int, std::unordered_set<unsigned int>> unaryFacts;
    // Key - Index of predicate | Value - List of combinations of objcets which the predicate is true for (Should be a set, but cpp has a stroke trying to has a vector)
    std::unordered_map<unsigned int, std::vector<MultiFact>> multiFacts;

    PDDLState() {};
    PDDLState(std::unordered_map<unsigned int, std::unordered_set<unsigned int>> unaryFacts, std::unordered_map<unsigned int, std::vector<MultiFact>> multiFacts) :
        unaryFacts(unaryFacts), multiFacts(multiFacts) {};
    
    // Very slow, please only use with caution
    friend bool operator== (const PDDLState &lhs, const PDDLState &rhs) {
        // Check unary facts
        //// Check that they contain the same keys
        for (auto iter : lhs.unaryFacts)
            if (!rhs.unaryFacts.contains(iter.first))
                return false;
        for (auto iter : rhs.unaryFacts)
            if (!lhs.unaryFacts.contains(iter.first))
                return false;
        //// 
        //// Check that they contain the same values
        for (auto iter : lhs.unaryFacts)
            if (lhs.unaryFacts.at(iter.first) != rhs.unaryFacts.at(iter.first))
                return false;
        ////
        //
        // Check multi facts
        //// Check that they contain the same keys
        for (auto iter : lhs.multiFacts)
            if (!rhs.multiFacts.contains(iter.first))
                return false;
        for (auto iter : rhs.multiFacts)
            if (!lhs.multiFacts.contains(iter.first))
                return false;
        //// 
        //// Check that they contain the same values
        for (auto iter : lhs.multiFacts)
            for (auto vIter : iter.second) {
                auto AreEqual = [&vIter](const MultiFact &MF) {
                    return vIter == MF;
                };
                if (!std::any_of(rhs.multiFacts.at(iter.first).begin(), rhs.multiFacts.at(iter.first).end(), AreEqual))
                    return false;
            }
        for (auto iter : rhs.multiFacts)
            for (auto vIter : iter.second) {
                auto AreEqual = [&vIter](const MultiFact &MF) {
                    return vIter == MF;
                };
                if (!std::any_of(lhs.multiFacts.at(iter.first).begin(), lhs.multiFacts.at(iter.first).end(), AreEqual))
                    return false;
            }
        ////
        // 

        return true;
    };
};

#endif
