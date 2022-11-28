#include <catch2/catch_test_macros.hpp>

#include <vector>

#include "../../src/JointPaths/Finder/Finder.hh"
#include "../../src/Walker/Path.hh"

using namespace std;
using namespace JointPaths;

const std::string TAG = "JointPaths-Finder ";

#pragma region Can_FindLargeOccurance

TEST_CASE(TAG + "Can_FindLargeOccurance_1") {
    PDDL::Action constantAction = PDDL::Action("Action-1");
    PDDL::ActionInstance constantInstance(&constantAction, {});
    vector<Path> paths = { 
        Path({ constantInstance,constantInstance,constantInstance,constantInstance }),
        Path({ constantInstance,constantInstance,constantInstance,constantInstance }) };

    auto data = Finder::RunData();
    data.SearchFloor = 4;
    Finder finder(data);
    auto result = finder.FindEntangledCandidates(&paths);
    REQUIRE(result.size() == 1);
    auto firstObject = *result.begin();
    REQUIRE(firstObject.second.Chain.size() == 4);
    REQUIRE(firstObject.second.Occurance == 2);
}

TEST_CASE(TAG + "Can_FindLargeOccurance_2") {
    PDDL::Action constantAction1 = PDDL::Action("Action-1");
    PDDL::ActionInstance constantInstance1(&constantAction1, {});
    PDDL::Action constantAction2 = PDDL::Action("Action-2");
    PDDL::ActionInstance constantInstance2(&constantAction2, {});

    vector<Path> paths = {
        Path({ constantInstance1,constantInstance2,constantInstance2,constantInstance1 }),
        Path({ constantInstance1,constantInstance2,constantInstance2,constantInstance1 }),
        Path({ constantInstance1,constantInstance2,constantInstance2,constantInstance1 }),
        Path({ constantInstance1,constantInstance2,constantInstance2,constantInstance1 }) };

    auto data = Finder::RunData();
    data.SearchFloor = 4;
    Finder finder(data);
    auto result = finder.FindEntangledCandidates(&paths);
    REQUIRE(result.size() == 1);
    auto firstObject = *result.begin();
    REQUIRE(firstObject.second.Chain.size() == 4);
    REQUIRE(firstObject.second.Occurance == 4);
}

TEST_CASE(TAG + "Can_FindLargeOccurance_3") {
    PDDL::Action constantAction1 = PDDL::Action("Action-1");
    PDDL::ActionInstance constantInstance1(&constantAction1, {});
    PDDL::Action constantAction2 = PDDL::Action("Action-2");
    PDDL::ActionInstance constantInstance2(&constantAction2, {});

    vector<Path> paths = {
        Path({ constantInstance2,constantInstance2,constantInstance1,constantInstance1 }),
        Path({ constantInstance2,constantInstance2,constantInstance1,constantInstance1 }),
        Path({ constantInstance1,constantInstance2,constantInstance2,constantInstance1 }),
        Path({ constantInstance1,constantInstance2,constantInstance2,constantInstance1 }) };

    auto data = Finder::RunData();
    data.SearchFloor = 4;
    Finder finder(data);
    auto result = finder.FindEntangledCandidates(&paths);
    REQUIRE(result.size() == 2);
    for(auto i = result.begin(); i != result.end(); i++)
        REQUIRE((*i).second.Chain.size() == 4);
}

TEST_CASE(TAG + "Can_FindLargeOccurance_Uneven_1") {
    PDDL::Action constantAction1 = PDDL::Action("Action-1");
    PDDL::ActionInstance constantInstance1(&constantAction1, {});
    PDDL::Action constantAction2 = PDDL::Action("Action-2");
    PDDL::ActionInstance constantInstance2(&constantAction2, {});

    vector<Path> paths = {
        Path({ constantInstance2,constantInstance2,constantInstance1,constantInstance1 }),
        Path({ constantInstance2,constantInstance2,constantInstance1,constantInstance1 }),
        Path({ constantInstance2,constantInstance1 }),
        Path({ constantInstance1,constantInstance2,constantInstance2,constantInstance1 }),
        Path({ constantInstance2,constantInstance2,constantInstance1 }) };

    auto data = Finder::RunData();
    data.SearchFloor = 4;
    Finder finder(data);
    auto result = finder.FindEntangledCandidates(&paths);
    REQUIRE(result.size() == 1);
}

#pragma endregion

#pragma region Cant_FindLargeOccurance

TEST_CASE(TAG + "Cant_FindLargeOccurance_IfNotThere_1") {
    PDDL::Action constantAction1 = PDDL::Action("Action-1");
    PDDL::ActionInstance constantInstance1(&constantAction1, {});
    PDDL::Action constantAction2 = PDDL::Action("Action-2");
    PDDL::ActionInstance constantInstance2(&constantAction2, {});

    vector<Path> paths = {
        Path({ constantInstance1,constantInstance1,constantInstance2,constantInstance1 }),
        Path({ constantInstance1,constantInstance2,constantInstance1,constantInstance1 }) };

    auto data = Finder::RunData();
    data.SearchFloor = 4;
    Finder finder(data);
    auto result = finder.FindEntangledCandidates(&paths);
    REQUIRE(result.size() == 0);
}

TEST_CASE(TAG + "Cant_FindLargeOccurance_IfNotThere_2") {
    PDDL::Action constantAction1 = PDDL::Action("Action-1");
    PDDL::ActionInstance constantInstance1(&constantAction1, {});
    PDDL::Action constantAction2 = PDDL::Action("Action-2");
    PDDL::ActionInstance constantInstance2(&constantAction2, {});

    vector<Path> paths = {
        Path({ constantInstance1,constantInstance1,constantInstance1,constantInstance2 }),
        Path({ constantInstance1,constantInstance1,constantInstance2,constantInstance1 }),
        Path({ constantInstance1,constantInstance2,constantInstance1,constantInstance1 }),
        Path({ constantInstance2,constantInstance1,constantInstance1,constantInstance1 }) };

    auto data = Finder::RunData();
    data.SearchFloor = 4;
    Finder finder(data);
    auto result = finder.FindEntangledCandidates(&paths);
    REQUIRE(result.size() == 0);
}

#pragma endregion

#pragma region Can_FindMediumOccurance

TEST_CASE(TAG + "Can_FindMediumOccurance_1") {
    PDDL::Action constantAction1 = PDDL::Action("Action-1");
    PDDL::ActionInstance constantInstance1(&constantAction1, {});
    PDDL::Action constantAction2 = PDDL::Action("Action-2");
    PDDL::ActionInstance constantInstance2(&constantAction2, {});

    vector<Path> paths = {
        //      Should find this as an occurance
        //     | ------------------------------- |
        Path({ constantInstance1,constantInstance1,constantInstance2,constantInstance1 }),
        Path({ constantInstance1,constantInstance2,constantInstance1,constantInstance1 }) };

    auto data = Finder::RunData();
    data.SearchFloor = 2;
    Finder finder(data);
    auto result = finder.FindEntangledCandidates(&paths);
    REQUIRE(result.size() == 1);
}

TEST_CASE(TAG + "Can_FindMediumOccurance_Uneven_1") {
    PDDL::Action constantAction1 = PDDL::Action("Action-1");
    PDDL::ActionInstance constantInstance1(&constantAction1, {});
    PDDL::Action constantAction2 = PDDL::Action("Action-2");
    PDDL::ActionInstance constantInstance2(&constantAction2, {});

    vector<Path> paths = {
        //      Should find this as an occurance
        //     | ------------------------------- |
        Path({ constantInstance1,constantInstance1,constantInstance2,constantInstance1 }),
        Path({ constantInstance1,constantInstance2,constantInstance1,constantInstance1, constantInstance1 }) };

    auto data = Finder::RunData();
    data.SearchFloor = 2;
    Finder finder(data);
    auto result = finder.FindEntangledCandidates(&paths);
    REQUIRE(result.size() == 1);
}

TEST_CASE(TAG + "Can_FindMediumOccurance_Uneven_2") {
    PDDL::Action constantAction1 = PDDL::Action("Action-1");
    PDDL::ActionInstance constantInstance1(&constantAction1, {});
    PDDL::Action constantAction2 = PDDL::Action("Action-2");
    PDDL::ActionInstance constantInstance2(&constantAction2, {});

    vector<Path> paths = {
        //      Should find this as an occurance
        //     | ------------------------------- |
        Path({ constantInstance1,constantInstance1,constantInstance2,constantInstance1, constantInstance1 }),
        Path({ constantInstance1,constantInstance2,constantInstance1,constantInstance1 }) };

    auto data = Finder::RunData();
    data.SearchFloor = 2;
    Finder finder(data);
    auto result = finder.FindEntangledCandidates(&paths);
    REQUIRE(result.size() == 1);
}

TEST_CASE(TAG + "Can_FindMediumOccurance_Uneven_3") {
    PDDL::Action constantAction1 = PDDL::Action("Action-1");
    PDDL::ActionInstance constantInstance1(&constantAction1, {});
    PDDL::Action constantAction2 = PDDL::Action("Action-2");
    PDDL::ActionInstance constantInstance2(&constantAction2, {});

    vector<Path> paths = {
        //      Should find this as an occurance
        //     | ------------------------------- |
        Path({ constantInstance1,constantInstance1 }),
        Path({ constantInstance1,constantInstance2,constantInstance1,constantInstance1 }) };

    auto data = Finder::RunData();
    data.SearchFloor = 2;
    Finder finder(data);
    auto result = finder.FindEntangledCandidates(&paths);
    REQUIRE(result.size() == 1);
}

#pragma endregion

#pragma region Cant_FindMediumOccurance

TEST_CASE(TAG + "Cant_FindMediumOccurance_IfNotThere") {
    PDDL::Action constantAction1 = PDDL::Action("Action-1");
    PDDL::ActionInstance constantInstance1(&constantAction1, {});
    PDDL::Action constantAction2 = PDDL::Action("Action-2");
    PDDL::ActionInstance constantInstance2(&constantAction2, {});
    PDDL::Action constantAction3 = PDDL::Action("Action-3");
    PDDL::ActionInstance constantInstance3(&constantAction3, {});

    vector<Path> paths = {
        Path({ constantInstance1,constantInstance1,constantInstance1 }),
        Path({ constantInstance2,constantInstance2,constantInstance2 }),
        Path({ constantInstance3,constantInstance3,constantInstance3 }) };

    auto data = Finder::RunData();
    data.SearchFloor = 2;
    Finder finder(data);
    auto result = finder.FindEntangledCandidates(&paths);
    REQUIRE(result.size() == 0);
}

TEST_CASE(TAG + "Cant_FindMediumOccurance_IfNotThere_Uneven") {
    PDDL::Action constantAction1 = PDDL::Action("Action-1");
    PDDL::ActionInstance constantInstance1(&constantAction1, {});
    PDDL::Action constantAction2 = PDDL::Action("Action-2");
    PDDL::ActionInstance constantInstance2(&constantAction2, {});
    PDDL::Action constantAction3 = PDDL::Action("Action-3");
    PDDL::ActionInstance constantInstance3(&constantAction3, {});

    vector<Path> paths = {
        Path({ constantInstance1,constantInstance1,constantInstance1 }),
        Path({ constantInstance2 }),
        Path({ constantInstance3,constantInstance3 }) };

    auto data = Finder::RunData();
    data.SearchFloor = 2;
    Finder finder(data);
    auto result = finder.FindEntangledCandidates(&paths);
    REQUIRE(result.size() == 0);
}

#pragma endregion

#pragma region Can_FindSmallOccurance

TEST_CASE(TAG + "Can_FindSmallOccurance_1") {
    PDDL::Action constantAction1 = PDDL::Action("Action-1");
    PDDL::ActionInstance constantInstance1(&constantAction1, {});
    PDDL::Action constantAction2 = PDDL::Action("Action-2");
    PDDL::ActionInstance constantInstance2(&constantAction2, {});

    vector<Path> paths = {
        //      Should find this as an occurance
        //     | ------------------------------- |
        Path({ constantInstance1,constantInstance1,constantInstance2,constantInstance1, constantInstance1, constantInstance2 }),
        Path({ constantInstance1,constantInstance2,constantInstance1,constantInstance1, constantInstance1, constantInstance1 }) };

    auto data = Finder::RunData();
    data.SearchFloor = 2;
    Finder finder(data);
    auto result = finder.FindEntangledCandidates(&paths);
    REQUIRE(result.size() == 3);
}

#pragma endregion

#pragma region Cant_FindSmallOccurance

TEST_CASE(TAG + "Cant_FindSmallOccurance_1") {
    PDDL::Action constantAction1 = PDDL::Action("Action-1");
    PDDL::ActionInstance constantInstance1(&constantAction1, {});
    PDDL::Action constantAction2 = PDDL::Action("Action-2");
    PDDL::ActionInstance constantInstance2(&constantAction2, {});

    vector<Path> paths = {
        Path({ constantInstance1,constantInstance1 }),
        Path({ constantInstance2,constantInstance2 }) };

    auto data = Finder::RunData();
    data.SearchFloor = 2;
    Finder finder(data);
    auto result = finder.FindEntangledCandidates(&paths);
    REQUIRE(result.size() == 0);
}

#pragma endregion

