#include <catch2/catch_test_macros.hpp>

#include <vector>
#include <string>

#include "../../src/EntanglementFinder/EntanglementFinder.hh"
#include "../../src/Walker/Path.hpp"

int collisionDepth = 5000;
int currentCase = 1;
int totalCases = 17;
bool debugPrint = true;
void FinishedCase() {
    if (debugPrint)
        std::cout << "EntanglementFinder-Hashes - Finished " + std::to_string(currentCase++) + " out of " + std::to_string(totalCases) << std::endl;
}

using namespace std;

const std::string TAG = "EntanglementFinder-Hashes ";

#pragma region  PDDLActionInstance

TEST_CASE(TAG + "Can_Hash_PDDLActionInstance") {
    PDDLAction constantAction;
    PDDLActionInstance constantInstance(&constantAction, {1,2});

    auto hashValue = constantInstance.GetHash();

    REQUIRE(hashValue == 6505549070604997458);
    FinishedCase();
}

TEST_CASE(TAG + "Can_Hash_PDDLActionInstance_Objects_NoCollision_1") {
    unordered_set<size_t> hashes;
    vector<string> parameters;
    parameters.reserve(1);
    vector<PDDLLiteral> preconditions;
    vector<PDDLLiteral> effects;
    PDDLAction constantAction = PDDLAction("Name", parameters, preconditions, effects);
    for (int i = 0; i < collisionDepth; i++) {
        PDDLActionInstance constantInstance(&constantAction, { (unsigned int)i });
        auto hashValue = constantInstance.GetHash();
        REQUIRE(!hashes.contains(hashValue));
        hashes.emplace(hashValue);
    }
    FinishedCase();
}

TEST_CASE(TAG + "Can_Hash_PDDLActionInstance_Objects_NoCollision_2") {
    unordered_set<size_t> hashes;
    vector<string> parameters;
    parameters.reserve(2);
    vector<PDDLLiteral> preconditions;
    vector<PDDLLiteral> effects;
    PDDLAction constantAction = PDDLAction("Name", parameters, preconditions, effects);
    for (int i = 0; i < collisionDepth; i++) {
        PDDLActionInstance constantInstance(&constantAction, { (unsigned int)i, (unsigned int)i });
        auto hashValue = constantInstance.GetHash();
        REQUIRE(!hashes.contains(hashValue));
        hashes.emplace(hashValue);
    }
    FinishedCase();
}

TEST_CASE(TAG + "Can_Hash_PDDLActionInstance_Objects_NoCollision_3") {
    unordered_set<size_t> hashes;
    vector<string> parameters;
    parameters.reserve(3);
    vector<PDDLLiteral> preconditions;
    vector<PDDLLiteral> effects;
    PDDLAction constantAction = PDDLAction("Name", parameters, preconditions, effects);
    for (int i = 0; i < collisionDepth; i++) {
        PDDLActionInstance constantInstance(&constantAction, { (unsigned int)i, (unsigned int)i, (unsigned int)i });
        auto hashValue = constantInstance.GetHash();
        REQUIRE(!hashes.contains(hashValue));
        hashes.emplace(hashValue);
    }
    FinishedCase();
}

TEST_CASE(TAG + "Can_Hash_PDDLActionInstance_Objects_NoCollision_4") {
    unordered_set<size_t> hashes;
    PDDLAction constantAction;
    for (int i = 0; i < collisionDepth; i++) {
        PDDLActionInstance constantInstance(&constantAction, { (unsigned int)i });
        auto hashValue = constantInstance.GetHash();
        REQUIRE(!hashes.contains(hashValue));
        hashes.emplace(hashValue);
    }
    FinishedCase();
}

TEST_CASE(TAG + "Can_Hash_PDDLActionInstance_Objects_NoCollision_5") {
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
    FinishedCase();
}

TEST_CASE(TAG + "Can_Hash_PDDLActionInstance_Objects_Collision_1") {
    PDDLAction constantAction1;
    PDDLAction constantAction2;

    PDDLActionInstance constantInstance1(&constantAction1, { 1 });
    PDDLActionInstance constantInstance2(&constantAction2, { 1 });

    auto hashValue1 = constantInstance1.GetHash();
    auto hashValue2 = constantInstance2.GetHash();

    REQUIRE(hashValue1 == hashValue2);
    FinishedCase();
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
    FinishedCase();
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
    FinishedCase();
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
    FinishedCase();
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
    FinishedCase();
}

#pragma endregion

#pragma region vector<PDDLActionInstance>

TEST_CASE(TAG + "Can_Hash_PDDLActionInstance_Vector") {
    vector<PDDLActionInstance*> set;
    for (int i = 0; i < 10; i++) {
        PDDLAction constantAction;
        set.push_back(new PDDLActionInstance(&constantAction, { 1, 2, (unsigned int)i }));
    }

    auto hashValue = hash<vector<PDDLActionInstance*>>{}(set);

    REQUIRE(hashValue == 4344514121280611648);
    FinishedCase();
}

TEST_CASE(TAG + "Can_Hash_PDDLActionInstance_Vector_NoCollision_1") {
    unordered_set<size_t> hashes;
    for (int i = 0; i < collisionDepth; i++) {
        vector<PDDLActionInstance*> set;
        for (int j = i; j < i + 10; j++) {
            PDDLAction constantAction = PDDLAction("Name-" + to_string(j));
            set.push_back(new PDDLActionInstance(&constantAction, { 1, 2, (unsigned int)j }));
        }

        auto hashValue = hash<vector<PDDLActionInstance*>>{}(set);
        REQUIRE(!hashes.contains(hashValue));
        hashes.emplace(hashValue);
    }
    FinishedCase();
}

TEST_CASE(TAG + "Can_Hash_PDDLActionInstance_Vector_NoCollision_2") {
    unordered_set<size_t> hashes;
    for (int i = 0; i < collisionDepth; i++) {
        vector<PDDLActionInstance*> set;
        for (int j = 0; j < i; j++) {
            PDDLAction constantAction = PDDLAction("Name-" + to_string(j));
            set.push_back(new PDDLActionInstance(&constantAction, { 1, 2, (unsigned int)j }));
        }

        auto hashValue = hash<vector<PDDLActionInstance*>>{}(set);
        REQUIRE(!hashes.contains(hashValue));
        hashes.emplace(hashValue);
    }
    FinishedCase();
}

TEST_CASE(TAG + "Can_Hash_PDDLActionInstance_Vector_Collision_1") {
    
    size_t expectedHash = 2149843915544583187;

    for (int i = 0; i < collisionDepth; i++) {
        vector<PDDLActionInstance*> set;
        for (int j = 0; j < 2; j++) {
            PDDLAction constantAction = PDDLAction("Name-" + to_string(j));
            set.push_back(new PDDLActionInstance(&constantAction, { 1, 2, (unsigned int)j }));
        }

        auto hashValue = hash<vector<PDDLActionInstance*>>{}(set);
        REQUIRE(hashValue == expectedHash);
    }
    FinishedCase();
}

TEST_CASE(TAG + "Can_Hash_PDDLActionInstance_Vector_Collision_2") {

    size_t expectedHash = 1555253033455459816;

    for (int i = 0; i < collisionDepth; i++) {
        vector<PDDLActionInstance*> set;
        for (int j = 0; j < 10; j++) {
            PDDLAction constantAction = PDDLAction("Name-" + to_string(j));
            set.push_back(new PDDLActionInstance(&constantAction, { 1, 2, (unsigned int)j }));
        }

        auto hashValue = hash<vector<PDDLActionInstance*>>{}(set);
        REQUIRE(hashValue == expectedHash);
    }
    FinishedCase();
}

TEST_CASE(TAG + "Can_Hash_PDDLActionInstance_Vector_Collision_3") {

    size_t expectedHash = 16476306162301439505;

    for (int i = 0; i < collisionDepth; i++) {
        vector<PDDLActionInstance*> set;
        for (int j = 0; j < 100; j++) {
            PDDLAction constantAction = PDDLAction("Name-" + to_string(j));
            set.push_back(new PDDLActionInstance(&constantAction, { 1, 2, (unsigned int)j }));
        }

        auto hashValue = hash<vector<PDDLActionInstance*>>{}(set);
        REQUIRE(hashValue == expectedHash);
    }
    FinishedCase();
}

#pragma endregion
