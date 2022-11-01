#include <catch2/catch_test_macros.hpp>

#include <vector>

#include "../../src/EntanglementFinder/EntanglementFinder.hh"
#include "../../src/Walker/Walker.hpp"

using namespace std;

const std::string TAG = "EntanglementFinder-Hashes ";

TEST_CASE(TAG + "Can_Hash_PDDLActionInstance") {
    PDDLAction constantAction;
    PDDLActionInstance constantInstance(&constantAction, {1,2});

    auto hashValue = hash<PDDLActionInstance>{}(constantInstance);

    REQUIRE(hashValue == 140386992841570);
}
