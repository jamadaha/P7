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
    std::unordered_map<unsigned int, std::unordered_set<std::pair<unsigned int, unsigned int>>> binaryFacts;
    // Key - Index of predicate | Value - List of permutations of objcets which the predicate is true for
    std::unordered_map<unsigned int, std::unordered_set<MultiFact>> multiFacts;

    PDDLState() {};
    PDDLState(std::unordered_map<unsigned int, std::unordered_set<unsigned int>> unaryFacts, 
              std::unordered_map<unsigned int, std::unordered_set<std::pair<unsigned int, unsigned int>>> binaryFacts, 
              std::unordered_map<unsigned int, std::unordered_set<MultiFact>> multiFacts) :
        unaryFacts(unaryFacts), binaryFacts(binaryFacts), multiFacts(multiFacts) {};

    std::size_t GetHash();

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
};

namespace std {
    template <>
    struct hash<PDDLState> {
        auto operator()(PDDLState& s) const -> size_t {
            size_t hashValue = s.unaryFacts.size();
            hashValue = (s.unaryFacts.size() * (s.binaryFacts.size() << 1)) ^ (s.multiFacts.size() << 1);
            for (auto i : s.unaryFacts)
                hashValue ^= hash<unordered_set<unsigned int>>{}(i.second) << (s.unaryFacts.size() * i.first);
            for (auto i : s.binaryFacts)
                for (auto j : i.second)
                    hashValue ^= s.binaryFacts.size() << (i.first ^ (j.first * j.second));
            for (auto i : s.multiFacts) {
                for (auto j : i.second) {
                    size_t multiHash = hash<MultiFact>{}(j);
                    hashValue ^= i.first >> multiHash;
                }
            }
            return hashValue;
        }
    };
}

#endif
