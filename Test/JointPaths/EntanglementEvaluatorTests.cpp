#include <catch2/catch_test_macros.hpp>

#include <vector>

#include "../../src/EntanglementFinder/EntanglementEvaluator.hh"
#include "../../src/Walker/Path.hh"

using namespace std;

const std::string TAG = "EntanglementEvaluator ";

TEST_CASE(TAG + "Can_FindLargeOccurance_1") {
    PDDLAction constantAction = PDDLAction("Action-1");
    PDDLActionInstance constantInstance(&constantAction, {});
    vector<Path> paths = {
        Path({ constantInstance,constantInstance,constantInstance,constantInstance }),
        Path({ constantInstance,constantInstance,constantInstance,constantInstance }) };

    auto data = EntanglementFinder::RunData();
    data.SearchFloor = 4;
    EntanglementFinder finder(data);
    auto result = finder.FindEntangledCandidates(&paths);
    REQUIRE(result.size() == 1);
    auto firstObject = *result.begin();
    REQUIRE(firstObject.second.Chain.size() == 4);
    REQUIRE(firstObject.second.Occurance == 2);
}
