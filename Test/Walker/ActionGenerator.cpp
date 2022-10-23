#include <catch2/catch_test_macros.hpp>

#include "../../src/IntermediatePDDL/PDDLInstance.hh"
#include "../../src/Walker/ActionGenerator.hpp"

const std::string TAG = "ActionGenerator ";

std::vector<std::unordered_set<unsigned int>> GetCandidateObjectsPlaceholder(const unsigned int setCount, const unsigned int setSize) {
    std::vector<std::unordered_set<unsigned int>> candidateObjects;
    candidateObjects.reserve(setCount);
    for (int i = 0; i < setCount; i++) {
        std::unordered_set<unsigned int> tempSet;
        tempSet.reserve(setSize);
        for (int t = 0; t < setSize; t++)
            tempSet.emplace(t);
        candidateObjects.push_back(tempSet);
    }
    return candidateObjects;
}

std::vector<std::unordered_set<unsigned int>::iterator> GetIterators(std::vector<std::unordered_set<unsigned int>> &candidateObjects) {
    std::vector<std::unordered_set<unsigned int>::iterator> iterators;
    iterators.reserve(candidateObjects.size());
    for (int i = 0; i < candidateObjects.size(); i++)
        iterators.push_back(candidateObjects.at(i).begin());
    return iterators;
}

// static bool Iterate(std::vector<std::unordered_set<unsigned int>::iterator> *iteration, std::vector<std::unordered_set<unsigned int>> *candidateObjects);
TEST_CASE("Iterate"){
    SECTION("Single Iteration") {
        auto candidateObjects = GetCandidateObjectsPlaceholder(2, 2);
        auto iteration = GetIterators(candidateObjects);
        REQUIRE(2 == iteration.size());
        std::vector<unsigned int> before;
        for (int i = 0; i < iteration.size(); i++)
            before.push_back(*iteration.at(i));
        REQUIRE(ActionGenerator::Iterate(&iteration, &candidateObjects));
        std::vector<unsigned int> after;
        for (int i = 0; i < iteration.size(); i++)
            after.push_back(*iteration.at(i));
        REQUIRE(before.at(0) != after.at(0));
        REQUIRE(before.at(1) == after.at(1));
    }

    SECTION("Overflow") {
        auto candidateObjects = GetCandidateObjectsPlaceholder(2, 2);
        auto iteration = GetIterators(candidateObjects);
        REQUIRE(2 == iteration.size());
        std::vector<unsigned int> before;
        for (int i = 0; i < iteration.size(); i++)
            before.push_back(*iteration.at(i));
        for (int i = 0; i < 2; i++)
            REQUIRE(ActionGenerator::Iterate(&iteration, &candidateObjects));
        std::vector<unsigned int> after;
        for (int i = 0; i < iteration.size(); i++)
            after.push_back(*iteration.at(i));
        REQUIRE(before.at(1) != after.at(1));
        REQUIRE(before.at(0) == after.at(0));
    }

    SECTION("End") {
        auto candidateObjects = GetCandidateObjectsPlaceholder(2, 2);
        auto iteration = GetIterators(candidateObjects);
        REQUIRE(2 == iteration.size());
        for (int i = 0; i < 4; i++) {
            printf("%u %u\n", (*iteration.at(0)), (*iteration.at(1)));
            if (i != 3)
                REQUIRE(ActionGenerator::Iterate(&iteration, &candidateObjects));
            else
                REQUIRE(!ActionGenerator::Iterate(&iteration, &candidateObjects));
        }
    }
}


