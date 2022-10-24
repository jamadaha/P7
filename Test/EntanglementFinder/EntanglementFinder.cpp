#include <catch2/catch_test_macros.hpp>

#include <vector>

#include "../../src/EntanglementFinder/EntanglementFinder.hh"
#include "../../src/Walker/Walker.hpp"

using namespace std;

const std::string TAG = "EntanglementFinder ";

#pragma region Can_FindLargeOccurance

TEST_CASE(TAG + "Can_FindLargeOccurance_1") {
    PDDLAction constantAction;
    PDDLActionInstance constantInstance(&constantAction, {});
    vector<Path> paths = { 
        Path({ constantInstance,constantInstance,constantInstance,constantInstance }),
        Path({ constantInstance,constantInstance,constantInstance,constantInstance }) };

    EntanglementFinder finder(4, -1, 2, 0);
    auto result = finder.FindEntangledCandidates(paths);
    REQUIRE(result.size() == 1);
    auto firstObject = *result.begin();
    REQUIRE(firstObject.Chain.size() == 4);
    REQUIRE(firstObject.Occurance == 1);
}

TEST_CASE(TAG + "Can_FindLargeOccurance_2") {
    PDDLAction constantAction1;
    PDDLActionInstance constantInstance1(&constantAction1, {});
    PDDLAction constantAction2;
    PDDLActionInstance constantInstance2(&constantAction2, {});

    vector<Path> paths = {
        Path({ constantInstance1,constantInstance2,constantInstance2,constantInstance1 }),
        Path({ constantInstance1,constantInstance2,constantInstance2,constantInstance1 }),
        Path({ constantInstance1,constantInstance2,constantInstance2,constantInstance1 }),
        Path({ constantInstance1,constantInstance2,constantInstance2,constantInstance1 }) };

    EntanglementFinder finder(4);
    auto result = finder.FindEntangledCandidates(paths);
    REQUIRE(result.size() == 1);
    auto firstObject = *result.begin();
    REQUIRE(firstObject.Chain.size() == 4);
    REQUIRE(firstObject.Occurance == 6);
}

TEST_CASE(TAG + "Can_FindLargeOccurance_3") {
    PDDLAction constantAction1;
    PDDLActionInstance constantInstance1(&constantAction1, {});
    PDDLAction constantAction2;
    PDDLActionInstance constantInstance2(&constantAction2, {});

    vector<Path> paths = {
        Path({ constantInstance2,constantInstance2,constantInstance1,constantInstance1 }),
        Path({ constantInstance2,constantInstance2,constantInstance1,constantInstance1 }),
        Path({ constantInstance1,constantInstance2,constantInstance2,constantInstance1 }),
        Path({ constantInstance1,constantInstance2,constantInstance2,constantInstance1 }) };

    EntanglementFinder finder(4, -1, 2, 0);
    auto result = finder.FindEntangledCandidates(paths);
    REQUIRE(result.size() == 2);
    for(auto i = result.begin(); i != result.end(); i++)
        REQUIRE((*i).Chain.size() == 4);
}

#pragma endregion

#pragma region Cant_FindLargeOccurance

TEST_CASE(TAG + "Cant_FindLargeOccurance_IfNotThere_1") {
    PDDLAction constantAction1;
    PDDLActionInstance constantInstance1(&constantAction1, {});
    PDDLAction constantAction2;
    PDDLActionInstance constantInstance2(&constantAction2, {});

    vector<Path> paths = {
        Path({ constantInstance1,constantInstance1,constantInstance2,constantInstance1 }),
        Path({ constantInstance1,constantInstance2,constantInstance1,constantInstance1 }) };

    EntanglementFinder finder(4);
    auto result = finder.FindEntangledCandidates(paths);
    REQUIRE(result.size() == 0);
}

TEST_CASE(TAG + "Cant_FindLargeOccurance_IfNotThere_2") {
    PDDLAction constantAction1;
    PDDLActionInstance constantInstance1(&constantAction1, {});
    PDDLAction constantAction2;
    PDDLActionInstance constantInstance2(&constantAction2, {});

    vector<Path> paths = {
        Path({ constantInstance1,constantInstance1,constantInstance1,constantInstance2 }),
        Path({ constantInstance1,constantInstance1,constantInstance2,constantInstance1 }),
        Path({ constantInstance1,constantInstance2,constantInstance1,constantInstance1 }),
        Path({ constantInstance2,constantInstance1,constantInstance1,constantInstance1 }) };

    EntanglementFinder finder(4);
    auto result = finder.FindEntangledCandidates(paths);
    REQUIRE(result.size() == 0);
}

#pragma endregion