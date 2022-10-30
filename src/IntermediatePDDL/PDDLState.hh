#ifndef PDDL_STATE_HH
#define PDDL_STATE_HH

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <string>

#include "PDDLActionInstance.hh"
#include "../Helpers/Hashes.hh"

struct PDDLInstance;

struct MultiFact {
    std::vector<unsigned int> fact;
    MultiFact(std::vector<unsigned int> fact) : fact(fact) {};
    MultiFact(const std::vector<unsigned int> *indexes, const std::vector<unsigned int> *objects) {
        fact.reserve(indexes->size());
        for (int i = 0; i < indexes->size(); i++)
            fact.push_back(objects->at(indexes->at(i)));
    };

#pragma region Operators
#pragma region Equality
    friend bool operator== (const MultiFact &lhs, const MultiFact &rhs) {
        return lhs.fact == rhs.fact;
    }

    friend bool operator== (const MultiFact &lhs, const std::vector<unsigned int> &rhs) {
        return lhs.fact == rhs;
    }

    friend bool operator== (const std::vector<unsigned int> &lhs, const MultiFact &rhs) {
        return lhs == rhs.fact;
    }
    friend bool operator== (const MultiFact &lhs, const std::pair<const std::vector<unsigned int>*, const std::vector<unsigned int>*> &rhs) {
        if (rhs.first->size() != lhs.fact.size())
                return false;
        for (int i = 0; i < rhs.first->size(); i++)
            if (rhs.second->at(rhs.first->at(i)) != lhs.fact.at(i))
                return false;
        return true;
    }
    friend bool operator== (const std::pair<const std::vector<unsigned int>*, const std::vector<unsigned int>*> &lhs, const MultiFact &rhs) {
        return rhs == lhs;
    }
#pragma endregion Equality
#pragma endregion Operators

private:
};

namespace std {
    template <>
    struct hash<MultiFact> {
        auto operator()(const MultiFact& s) const -> size_t {
            return hash<vector<unsigned int>>{}(s.fact);
        }
    };
}

struct PDDLState {
    // Key - Index of predicate | Value - Set of objects which the predicate is true for
    std::unordered_map<unsigned int, std::unordered_set<unsigned int>> unaryFacts;
    // Key - Index of predicate | Value - List of combinations of objcets which the predicate is true for (Should be a set, but cpp has a stroke trying to has a vector)
    std::unordered_map<unsigned int, std::unordered_set<MultiFact>> multiFacts;

    PDDLState() {};
    PDDLState(std::unordered_map<unsigned int, std::unordered_set<unsigned int>> unaryFacts, std::unordered_map<unsigned int, std::unordered_set<MultiFact>> multiFacts) :
        unaryFacts(unaryFacts), multiFacts(multiFacts) {};

#pragma region ContainsFact
    bool ContainsFact(const unsigned int key, const unsigned int value) const {
        return (unaryFacts.at(key).contains(value));
    };

    bool ContainsFact(const unsigned int key, const MultiFact *value) const {
        return multiFacts.at(key).contains(*value);
    };

    bool ContainsFact(const unsigned int &key, const std::vector<unsigned int> *indexes, const std::vector<unsigned int> *objects) const {
        return multiFacts.at(key).contains(MultiFact(indexes, objects));
    }
#pragma endregion ContainsFact

    void DoAction(const PDDLActionInstance *action);
    void UndoAction(const PDDLActionInstance *action);

    std::string ToString(const PDDLInstance* instance);

    // Very slow, please only use with caution
    friend bool operator== (const PDDLState &lhs, const PDDLState &rhs) {
        return (lhs.unaryFacts != rhs.unaryFacts || lhs.multiFacts != rhs.multiFacts);
    };
    
};

namespace std {
    template <>
    struct hash<PDDLState> {
        auto operator()(const PDDLState& s) const -> size_t {
            size_t h1 = s.unaryFacts.size();
            size_t h2 = s.multiFacts.size();
            return h1 ^ (h2 << 1);
        }
    };
}

#endif
