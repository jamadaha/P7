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
    MultiFact(const MultiFact &mf) : fact(mf.fact) {};

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
    size_t GetHash();
    // Key - Index of predicate | Value - Set of objects which the predicate is true for
    std::unordered_map<unsigned int, std::unordered_set<unsigned int>> unaryFacts;
    std::unordered_map<unsigned int, std::unordered_set<std::pair<unsigned int, unsigned int>>> binaryFacts;
    // Key - Index of predicate | Value - List of permutations of objcets which the predicate is true for
    std::unordered_map<unsigned int, std::unordered_set<MultiFact>> multiFacts;

    PDDLState() {};
    PDDLState(std::unordered_map<unsigned int, std::unordered_set<unsigned int>> unaryFacts, 
              std::unordered_map<unsigned int, std::unordered_set<std::pair<unsigned int, unsigned int>>> binaryFacts, 
              std::unordered_map<unsigned int, std::unordered_set<MultiFact>> multiFacts) :
        unaryFacts(unaryFacts), binaryFacts(binaryFacts), multiFacts(multiFacts) {};
    PDDLState(const PDDLState &state) : unaryFacts(state.unaryFacts), binaryFacts(state.binaryFacts), multiFacts(state.multiFacts) {};

#pragma region ContainsFact

    bool ContainsFact(const unsigned int &key, const unsigned int *value) const {
        return unaryFacts.at(key).contains(*value);
    };
    bool ContainsFact(const unsigned int &key, const unsigned int &value) const {
        return unaryFacts.at(key).contains(value);
    };

    bool ContainsFact(const unsigned int &key, const std::pair<unsigned int, unsigned int> &value) const {
        if (key == 0)
            return value.first == value.second;
        return binaryFacts.at(key).contains(value);
    }

    bool ContainsFact(const unsigned int &key, const MultiFact *value) const {
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
        return (lhs.unaryFacts == rhs.unaryFacts && lhs.binaryFacts == rhs.binaryFacts && lhs.multiFacts == rhs.multiFacts);
    };

private:
    size_t hashValue = 0;
    
};

namespace std {
    template <>
    struct hash<PDDLState> {
        auto operator()(const PDDLState& s) const -> size_t {
            size_t hashValue = 0;
            for (auto predicate : s.unaryFacts)
                for (auto object : predicate.second)
                    hashValue += predicate.first * object;
            for (auto predicate : s.binaryFacts)
                for (auto object : predicate.second)
                    hashValue += predicate.first * (object.first + object.second);
            return hashValue;
        }
    };
}

#endif
