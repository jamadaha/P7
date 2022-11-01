#include <catch2/catch_test_macros.hpp>
#include <string>
#include <unordered_set>

#include "../../src/MacroGenerator/MacroGenerator.hh"

const std::string TAG = "Macro ";

TEST_CASE(TAG + "two same simple actions") {
    std::vector<PDDLActionInstance*> actions;
    // set up simple action with 1 precondition and 1 effect
    PDDLAction _act = PDDLAction(
        "testaction",
        std::vector<std::string> {"?x", "?y"},
        std::vector<PDDLLiteral> {PDDLLiteral(1, std::vector<unsigned int> {0}, true)},
        std::vector<PDDLLiteral> {PDDLLiteral(2, std::vector<unsigned int> {1}, true)}
    );
    PDDLActionInstance act1 = PDDLActionInstance(&_act, std::vector<unsigned int> {0, 1});
    PDDLActionInstance act2 = PDDLActionInstance(&_act, std::vector<unsigned int> {0, 1});
    actions.push_back(&act1);
    actions.push_back(&act2);
    // generate macro
    MacroGenerator macroGenerator = MacroGenerator();
    Macro m = macroGenerator.GenerateMacro(&actions);
    // expected stuff
    std::unordered_map<GroundedLiteral, bool> expectedPrecons ({
        {GroundedLiteral(1, std::vector<unsigned int> {0}), true}
    });
    std::unordered_map<GroundedLiteral, bool> expectedEffects ({
        {GroundedLiteral(2, std::vector<unsigned int> {1}), true}
    });
    REQUIRE(m.groundedAction.parameters == std::unordered_set<unsigned int> {0, 1});
    REQUIRE(m.groundedAction.preconditions == expectedPrecons);
    REQUIRE(m.groundedAction.effects == expectedEffects);
}

TEST_CASE(TAG + "two different simple actions") {
    std::vector<PDDLActionInstance*> actions;
    PDDLAction _act1 = PDDLAction(
        "testaction1",
        std::vector<std::string> {"?x", "?y"},
        std::vector<PDDLLiteral> {PDDLLiteral(1, std::vector<unsigned int> {0}, true)},
        std::vector<PDDLLiteral> {PDDLLiteral(2, std::vector<unsigned int> {1}, true)}
    );
    PDDLAction _act2 = PDDLAction(
        "testaction2",
        std::vector<std::string> {"?x", "?y"},
        std::vector<PDDLLiteral> {PDDLLiteral(3, std::vector<unsigned int> {0}, false)},
        std::vector<PDDLLiteral> {PDDLLiteral(4, std::vector<unsigned int> {1}, true)}
    );
    PDDLActionInstance act1 = PDDLActionInstance(&_act1, std::vector<unsigned int> {0, 1});
    PDDLActionInstance act2 = PDDLActionInstance(&_act2, std::vector<unsigned int> {1, 3});
    actions.push_back(&act1);
    actions.push_back(&act2);
    // generate macro
    MacroGenerator macroGenerator = MacroGenerator();
    Macro m = macroGenerator.GenerateMacro(&actions);
    // expected stuff
    std::unordered_map<GroundedLiteral, bool> expectedPrecons ({
        {GroundedLiteral(1, std::vector<unsigned int> {0}), true},
        {GroundedLiteral(3, std::vector<unsigned int> {1}), false}
    });
    std::unordered_map<GroundedLiteral, bool> expectedEffects ({
        {GroundedLiteral(2, std::vector<unsigned int> {1}), true},
        {GroundedLiteral(4, std::vector<unsigned int> {3}), true}
    });
    REQUIRE(m.groundedAction.parameters == std::unordered_set<unsigned int> {0, 1, 3});
    REQUIRE(m.groundedAction.preconditions == expectedPrecons);
    REQUIRE(m.groundedAction.effects == expectedEffects);
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