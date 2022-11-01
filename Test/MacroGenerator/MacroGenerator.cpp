#include <catch2/catch_test_macros.hpp>
#include <string>
#include <unordered_set>

#include "../../src/MacroGenerator/MacroGenerator.hh"

const std::string TAG = "Macro ";

TEST_CASE(TAG + "two same simple actions") {
    std::vector<PDDLActionInstance*> actions;
    // set up simple action with 1 precondition and 1 effect
    PDDLAction act = PDDLAction(
        "testaction",
        std::vector<std::string> {"?x", "?y"},
        std::vector<PDDLLiteral> {PDDLLiteral(1, std::vector<unsigned int> {0}, true)},
        std::vector<PDDLLiteral> {PDDLLiteral(2, std::vector<unsigned int> {1}, true)}
    );
    PDDLActionInstance act1 = PDDLActionInstance(&act, std::vector<unsigned int> {0, 1});
    PDDLActionInstance act2 = PDDLActionInstance(&act, std::vector<unsigned int> {1, 2});
    actions.push_back(&act1);
    actions.push_back(&act2);
    // generate macro
    MacroGenerator macroGenerator = MacroGenerator();
    Macro m = macroGenerator.GenerateMacro(&actions);
    // expected stuff
    std::unordered_map<GroundedLiteral, bool> expectedPrecons ({
        {GroundedLiteral(1, std::vector<unsigned int> {0}), true},
        {GroundedLiteral(1, std::vector<unsigned int> {1}), true}
    });
    std::unordered_map<GroundedLiteral, bool> expectedEffects ({
        {GroundedLiteral(2, std::vector<unsigned int> {1}), true},
        {GroundedLiteral(2, std::vector<unsigned int> {2}), true}
    });
    REQUIRE(m.groundedAction.parameters == std::unordered_set<unsigned int> {0, 1, 2});
    REQUIRE(m.groundedAction.preconditions == expectedPrecons);
    REQUIRE(m.groundedAction.effects == expectedEffects);
}

TEST_CASE(TAG + "two different simple actions") {
    REQUIRE(1==0);
}

TEST_CASE(TAG + "overlapping preconditions") {
    REQUIRE(1==0);
}

TEST_CASE(TAG + "precon - positive eff") {
    REQUIRE(1==0);
}

TEST_CASE(TAG + "positive - negative eff") {
    REQUIRE(1==0);
}

TEST_CASE(TAG + "negative - positive eff") {
    REQUIRE(1==0);
}