#include <catch2/catch_test_macros.hpp>

#include <vector>

#include "../../src/EntanglementFinder/EntanglementFinder.hh"
#include "../../src/Walker/Walker.hpp"

int collisionDepth = 10000;

using namespace std;

const std::string TAG = "EntanglementFinder-Hashes ";

TEST_CASE(TAG + "Can_Hash_PDDLActionInstance") {
    PDDLAction constantAction;
    PDDLActionInstance constantInstance(&constantAction, {1,2});

    auto hashValue = constantInstance.GetHash();

    REQUIRE(hashValue == 350495520994);
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
