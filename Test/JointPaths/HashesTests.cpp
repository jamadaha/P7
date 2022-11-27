#include <catch2/catch_test_macros.hpp>

#include <vector>
#include <string>

#include "../../src/Walker/Path.hh"

int collisionDepth = 5000;
//int collisionDepth = 5;
int currentCase = 1;
int totalCases = 17;
bool debugPrint = true;
void FinishedCase() {
    if (debugPrint)
        std::cout << "JointPaths-Hashes - Finished " + std::to_string(currentCase++) + " out of " + std::to_string(totalCases) << std::endl;
}

using namespace std;

const std::string TAG = "JointPaths-Hashes ";

#pragma region  PDDL::ActionInstance

TEST_CASE(TAG + "Can_Hash_PDDLActionInstance") {
    PDDL::Action constantAction;
    PDDL::ActionInstance constantInstance(&constantAction, {1,2});

    auto hashValue = constantInstance.GetHash();

    REQUIRE(hashValue == 6505549070604997458);
    FinishedCase();
}

TEST_CASE(TAG + "Can_Hash_PDDLActionInstance_Objects_NoCollision_1") {
    unordered_set<size_t> hashes;
    vector<string> parameters;
    parameters.reserve(1);
    vector<PDDL::Literal> preconditions;
    vector<PDDL::Literal> effects;
    PDDL::Action constantAction = PDDL::Action("Name", parameters, preconditions, effects);
    for (int i = 0; i < collisionDepth; i++) {
        PDDL::ActionInstance constantInstance(&constantAction, { (unsigned int)i });
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
    vector<PDDL::Literal> preconditions;
    vector<PDDL::Literal> effects;
    PDDL::Action constantAction = PDDL::Action("Name", parameters, preconditions, effects);
    for (int i = 0; i < collisionDepth; i++) {
        PDDL::ActionInstance constantInstance(&constantAction, { (unsigned int)i, (unsigned int)i });
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
    vector<PDDL::Literal> preconditions;
    vector<PDDL::Literal> effects;
    PDDL::Action constantAction = PDDL::Action("Name", parameters, preconditions, effects);
    for (int i = 0; i < collisionDepth; i++) {
        PDDL::ActionInstance constantInstance(&constantAction, { (unsigned int)i, (unsigned int)i, (unsigned int)i });
        auto hashValue = constantInstance.GetHash();
        REQUIRE(!hashes.contains(hashValue));
        hashes.emplace(hashValue);
    }
    FinishedCase();
}

TEST_CASE(TAG + "Can_Hash_PDDLActionInstance_Objects_NoCollision_4") {
    unordered_set<size_t> hashes;
    PDDL::Action constantAction;
    for (int i = 0; i < collisionDepth; i++) {
        PDDL::ActionInstance constantInstance(&constantAction, { (unsigned int)i });
        auto hashValue = constantInstance.GetHash();
        REQUIRE(!hashes.contains(hashValue));
        hashes.emplace(hashValue);
    }
    FinishedCase();
}

TEST_CASE(TAG + "Can_Hash_PDDLActionInstance_Objects_NoCollision_5") {
    unordered_set<size_t> hashes;
    PDDL::Action constantAction;
    for (int i = 0; i < collisionDepth; i++) {
        vector<unsigned int> objects;
        for (int j = 0; j < i; j++)
            objects.push_back(j);

        PDDL::ActionInstance constantInstance(&constantAction, { objects });
        auto hashValue = constantInstance.GetHash();
        REQUIRE(!hashes.contains(hashValue));
        hashes.emplace(hashValue);
    }
    FinishedCase();
}

TEST_CASE(TAG + "Can_Hash_PDDLActionInstance_Objects_Collision_1") {
    PDDL::Action constantAction1;
    PDDL::Action constantAction2;

    PDDL::ActionInstance constantInstance1(&constantAction1, { 1 });
    PDDL::ActionInstance constantInstance2(&constantAction2, { 1 });

    auto hashValue1 = constantInstance1.GetHash();
    auto hashValue2 = constantInstance2.GetHash();

    REQUIRE(hashValue1 == hashValue2);
    FinishedCase();
}

TEST_CASE(TAG + "Can_Hash_PDDLActionInstance_Objects_Collision_2") {
    PDDL::Action constantAction1;
    PDDL::Action constantAction2;

    vector<unsigned int> objects1;
    vector<unsigned int> objects2;
    for (int i = 0; i < 100; i++){
        objects1.push_back(i);
        objects2.push_back(i);
    }
    PDDL::ActionInstance constantInstance1(&constantAction1, objects1);
    PDDL::ActionInstance constantInstance2(&constantAction2, objects2);

    auto hashValue1 = constantInstance1.GetHash();
    auto hashValue2 = constantInstance2.GetHash();

    REQUIRE(hashValue1 == hashValue2);
    FinishedCase();
}

TEST_CASE(TAG + "Can_Hash_PDDLActionInstance_Action_NoCollision_1") {
    unordered_set<size_t> hashes;
    for (int i = 0; i < collisionDepth; i++) {
        PDDL::Action constantAction = PDDL::Action("Name " + to_string(i));
        PDDL::ActionInstance constantInstance(&constantAction, { 1 });
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
        vector<PDDL::Literal> preconditions;
        preconditions.reserve(i);
        vector<PDDL::Literal> effects;
        effects.reserve(i);

        PDDL::Action constantAction = PDDL::Action("Name" + to_string(i), parameters, preconditions, effects);
        PDDL::ActionInstance constantInstance(&constantAction, { 1 });
        auto hashValue = constantInstance.GetHash();
        REQUIRE(!hashes.contains(hashValue));
        hashes.emplace(hashValue);
    }
    FinishedCase();
}

TEST_CASE(TAG + "Can_Hash_PDDLActionInstance_Action_Collision_1") {
    vector<string> parameters1;
    vector<PDDL::Literal> preconditions1;
    vector<PDDL::Literal> effects1;
    PDDL::Action constantAction1 = PDDL::Action("Name", parameters1, preconditions1, effects1);
    PDDL::ActionInstance constantInstance1(&constantAction1, { 1 });

    vector<string> parameters2;
    vector<PDDL::Literal> preconditions2;
    vector<PDDL::Literal> effects2;
    PDDL::Action constantAction2 = PDDL::Action("Name", parameters2, preconditions2, effects2);
    PDDL::ActionInstance constantInstance2(&constantAction2, { 1 });

    REQUIRE(constantInstance1.GetHash() == constantInstance2.GetHash());
    FinishedCase();
}

#pragma endregion

#pragma region vector<PDDL::ActionInstance>

TEST_CASE(TAG + "Can_Hash_PDDLActionInstance_Vector") {
    vector<PDDL::ActionInstance*> set;
    for (int i = 0; i < 10; i++) {
        PDDL::Action constantAction;
        set.push_back(new PDDL::ActionInstance(&constantAction, { 1, 2, (unsigned int)i }));
    }

    auto hashValue = hash<vector<PDDL::ActionInstance*>>{}(set);

    REQUIRE(hashValue == 4344514121280611648);
    FinishedCase();
}

TEST_CASE(TAG + "Can_Hash_PDDLActionInstance_Vector_NoCollision_1") {
    unordered_set<size_t> hashes;
    for (int i = 0; i < collisionDepth; i++) {
        vector<PDDL::ActionInstance*> set;
        for (int j = i; j < i + 10; j++) {
            PDDL::Action constantAction = PDDL::Action("Name-" + to_string(j));
            set.push_back(new PDDL::ActionInstance(&constantAction, { 1, 2, (unsigned int)j }));
        }

        auto hashValue = hash<vector<PDDL::ActionInstance*>>{}(set);
        REQUIRE(!hashes.contains(hashValue));
        hashes.emplace(hashValue);
    }
    FinishedCase();
}

TEST_CASE(TAG + "Can_Hash_PDDLActionInstance_Vector_NoCollision_2") {
    unordered_set<size_t> hashes;
    for (int i = 0; i < collisionDepth; i++) {
        vector<PDDL::ActionInstance*> set;
        for (int j = 0; j < i; j++) {
            PDDL::Action constantAction = PDDL::Action("Name-" + to_string(j));
            set.push_back(new PDDL::ActionInstance(&constantAction, { 1, 2, (unsigned int)j }));
        }

        auto hashValue = hash<vector<PDDL::ActionInstance*>>{}(set);
        REQUIRE(!hashes.contains(hashValue));
        hashes.emplace(hashValue);
    }
    FinishedCase();
}

TEST_CASE(TAG + "Can_Hash_PDDLActionInstance_Vector_Collision_1") {
    
    size_t expectedHash = 2149843915544583187;

    for (int i = 0; i < collisionDepth; i++) {
        vector<PDDL::ActionInstance*> set;
        for (int j = 0; j < 2; j++) {
            PDDL::Action constantAction = PDDL::Action("Name-" + to_string(j));
            set.push_back(new PDDL::ActionInstance(&constantAction, { 1, 2, (unsigned int)j }));
        }

        auto hashValue = hash<vector<PDDL::ActionInstance*>>{}(set);
        REQUIRE(hashValue == expectedHash);
    }
    FinishedCase();
}

TEST_CASE(TAG + "Can_Hash_PDDLActionInstance_Vector_Collision_2") {

    size_t expectedHash = 1555253033455459816;

    for (int i = 0; i < collisionDepth; i++) {
        vector<PDDL::ActionInstance*> set;
        for (int j = 0; j < 10; j++) {
            PDDL::Action constantAction = PDDL::Action("Name-" + to_string(j));
            set.push_back(new PDDL::ActionInstance(&constantAction, { 1, 2, (unsigned int)j }));
        }

        auto hashValue = hash<vector<PDDL::ActionInstance*>>{}(set);
        REQUIRE(hashValue == expectedHash);
    }
    FinishedCase();
}

TEST_CASE(TAG + "Can_Hash_PDDLActionInstance_Vector_Collision_3") {

    size_t expectedHash = 16476306162301439505;

    for (int i = 0; i < collisionDepth; i++) {
        vector<PDDL::ActionInstance*> set;
        for (int j = 0; j < 100; j++) {
            PDDL::Action constantAction = PDDL::Action("Name-" + to_string(j));
            set.push_back(new PDDL::ActionInstance(&constantAction, { 1, 2, (unsigned int)j }));
        }

        auto hashValue = hash<vector<PDDL::ActionInstance*>>{}(set);
        REQUIRE(hashValue == expectedHash);
    }
    FinishedCase();
}

#pragma endregion
