#include <catch2/catch_test_macros.hpp>

#include <vector>

#include "../../src/EntanglementFinder/EntanglementFinder.hh"
#include "../../src/Walker/Walker.hpp"

int collisionDepth = 100;

using namespace std;

const std::string TAG = "EntanglementFinder-Hashes ";

#pragma region  PDDLActionInstance

TEST_CASE(TAG + "Can_Hash_PDDLActionInstance") {
    PDDLAction constantAction;
    PDDLActionInstance constantInstance(&constantAction, {1,2});

    auto hashValue = constantInstance.GetHash();

    REQUIRE(hashValue == 6505548967629018342);
}

TEST_CASE(TAG + "Can_Hash_PDDLActionInstance_Objects_NoCollision_1") {
    unordered_set<size_t> hashes;
    PDDLAction constantAction;
    for (int i = 0; i < collisionDepth; i++) {
        PDDLActionInstance constantInstance(&constantAction, { (unsigned int)i, (unsigned int)i + 1, (unsigned int)i + 2 });
        auto hashValue = constantInstance.GetHash();
        REQUIRE(!hashes.contains(hashValue));
        hashes.emplace(hashValue);
    }
}

TEST_CASE(TAG + "Can_Hash_PDDLActionInstance_Objects_NoCollision_2") {
    unordered_set<size_t> hashes;
    PDDLAction constantAction;
    for (int i = 0; i < collisionDepth; i++) {
        PDDLActionInstance constantInstance(&constantAction, { (unsigned int)i });
        auto hashValue = constantInstance.GetHash();
        REQUIRE(!hashes.contains(hashValue));
        hashes.emplace(hashValue);
    }
}

TEST_CASE(TAG + "Can_Hash_PDDLActionInstance_Objects_NoCollision_3") {
    unordered_set<size_t> hashes;
    PDDLAction constantAction;
    for (int i = 0; i < collisionDepth; i++) {
        vector<unsigned int> objects;
        for (int j = 0; j < i; j++)
            objects.push_back(j);

        PDDLActionInstance constantInstance(&constantAction, { objects });
        auto hashValue = constantInstance.GetHash();
        REQUIRE(!hashes.contains(hashValue));
        hashes.emplace(hashValue);
    }
}

TEST_CASE(TAG + "Can_Hash_PDDLActionInstance_Objects_Collision_1") {
    PDDLAction constantAction1;
    PDDLAction constantAction2;

    PDDLActionInstance constantInstance1(&constantAction1, { 1 });
    PDDLActionInstance constantInstance2(&constantAction2, { 1 });

    auto hashValue1 = constantInstance1.GetHash();
    auto hashValue2 = constantInstance2.GetHash();

    REQUIRE(hashValue1 == hashValue2);
}

TEST_CASE(TAG + "Can_Hash_PDDLActionInstance_Objects_Collision_2") {
    PDDLAction constantAction1;
    PDDLAction constantAction2;

    vector<unsigned int> objects1;
    vector<unsigned int> objects2;
    for (int i = 0; i < 100; i++){
        objects1.push_back(i);
        objects2.push_back(i);
    }
    PDDLActionInstance constantInstance1(&constantAction1, objects1);
    PDDLActionInstance constantInstance2(&constantAction2, objects2);

    auto hashValue1 = constantInstance1.GetHash();
    auto hashValue2 = constantInstance2.GetHash();

    REQUIRE(hashValue1 == hashValue2);
}

TEST_CASE(TAG + "Can_Hash_PDDLActionInstance_Action_NoCollision_1") {
    unordered_set<size_t> hashes;
    for (int i = 0; i < collisionDepth; i++) {
        PDDLAction constantAction = PDDLAction("Name " + to_string(i));
        PDDLActionInstance constantInstance(&constantAction, { 1 });
        auto hashValue = constantInstance.GetHash();
        REQUIRE(!hashes.contains(hashValue));
        hashes.emplace(hashValue);
    }
}

TEST_CASE(TAG + "Can_Hash_PDDLActionInstance_Action_NoCollision_2") {
    unordered_set<size_t> hashes;
    for (int i = 0; i < collisionDepth; i++) {
        vector<string> parameters;
        parameters.reserve(i);
        vector<PDDLLiteral> preconditions;
        preconditions.reserve(i);
        vector<PDDLLiteral> effects;
        effects.reserve(i);

        PDDLAction constantAction = PDDLAction("Name" + to_string(i), parameters, preconditions, effects);
        PDDLActionInstance constantInstance(&constantAction, { 1 });
        auto hashValue = constantInstance.GetHash();
        REQUIRE(!hashes.contains(hashValue));
        hashes.emplace(hashValue);
    }
}

TEST_CASE(TAG + "Can_Hash_PDDLActionInstance_Action_Collision_1") {
    vector<string> parameters1;
    vector<PDDLLiteral> preconditions1;
    vector<PDDLLiteral> effects1;
    PDDLAction constantAction1 = PDDLAction("Name", parameters1, preconditions1, effects1);
    PDDLActionInstance constantInstance1(&constantAction1, { 1 });

    vector<string> parameters2;
    vector<PDDLLiteral> preconditions2;
    vector<PDDLLiteral> effects2;
    PDDLAction constantAction2 = PDDLAction("Name", parameters2, preconditions2, effects2);
    PDDLActionInstance constantInstance2(&constantAction2, { 1 });

    REQUIRE(constantInstance1.GetHash() == constantInstance2.GetHash());
}

#pragma endregion


