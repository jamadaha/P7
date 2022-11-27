#include <catch2/catch_test_macros.hpp>
#include <string>
#include <unordered_set>

#include "../../src/MacroGenerator/MacroGenerator.hh"

const std::string TAG = "Macro ";

TEST_CASE(TAG + "two same simple actions") {
    std::vector<PDDL::ActionInstance> actions;
    // set up simple action with 1 precondition and 1 effect
    PDDL::Action _act = PDDL::Action(
        "testaction",
        std::vector<std::string> {"?x", "?y"},
        std::vector<PDDL::Literal> {PDDL::Literal(1, std::vector<unsigned int> {0}, true)},
        std::vector<PDDL::Literal> {PDDL::Literal(2, std::vector<unsigned int> {1}, true)}
    );
    PDDL::ActionInstance act1 = PDDL::ActionInstance(&_act, std::vector<unsigned int> {0, 1});
    PDDL::ActionInstance act2 = PDDL::ActionInstance(&_act, std::vector<unsigned int> {0, 1});
    actions.push_back(act1);
    actions.push_back(act2);
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
    std::vector<PDDL::ActionInstance> actions;
    PDDL::Action _act1 = PDDL::Action(
        "testaction1",
        std::vector<std::string> {"?x", "?y"},
        std::vector<PDDL::Literal> {PDDL::Literal(1, std::vector<unsigned int> {0}, true)},
        std::vector<PDDL::Literal> {PDDL::Literal(2, std::vector<unsigned int> {1}, true)}
    );
    PDDL::Action _act2 = PDDL::Action(
        "testaction2",
        std::vector<std::string> {"?x", "?y"},
        std::vector<PDDL::Literal> {PDDL::Literal(3, std::vector<unsigned int> {0}, false)},
        std::vector<PDDL::Literal> {PDDL::Literal(4, std::vector<unsigned int> {1}, true)}
    );
    PDDL::ActionInstance act1 = PDDL::ActionInstance(&_act1, std::vector<unsigned int> {0, 1});
    PDDL::ActionInstance act2 = PDDL::ActionInstance(&_act2, std::vector<unsigned int> {1, 3});
    actions.push_back(act1);
    actions.push_back(act2);
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
    std::vector<PDDL::ActionInstance> actions;
    PDDL::Action _act1 = PDDL::Action(
        "testaction1",
        std::vector<std::string> {"?x", "?y"},
        std::vector<PDDL::Literal> {PDDL::Literal(1, std::vector<unsigned int> {0}, true)},
        std::vector<PDDL::Literal> {PDDL::Literal(2, std::vector<unsigned int> {1}, true)}
    );
    PDDL::Action _act2 = PDDL::Action(
        "testaction2",
        std::vector<std::string> {"?x", "?y"},
        std::vector<PDDL::Literal> {PDDL::Literal(2, std::vector<unsigned int> {0}, true)},
        std::vector<PDDL::Literal> {PDDL::Literal(4, std::vector<unsigned int> {1}, true)}
    );
    PDDL::ActionInstance act1 = PDDL::ActionInstance(&_act1, std::vector<unsigned int> {0, 1});
    PDDL::ActionInstance act2 = PDDL::ActionInstance(&_act2, std::vector<unsigned int> {1, 2});

    actions.push_back(act1);
    actions.push_back(act2);

    // generate macro
    MacroGenerator macroGenerator = MacroGenerator();
    Macro m = macroGenerator.GenerateMacro(&actions);
    // expected stuff
    std::unordered_map<GroundedLiteral, bool> expectedPrecons ({
        {GroundedLiteral(1, std::vector<unsigned int> {0}), true}
        // PDDL::Literal with predicate 2 should be absent
    });
    std::unordered_map<GroundedLiteral, bool> expectedEffects ({
        {GroundedLiteral(2, std::vector<unsigned int> {1}), true},
        {GroundedLiteral(4, std::vector<unsigned int> {2}), true}
    });
    REQUIRE(m.groundedAction.parameters == std::unordered_set<unsigned int> {0, 1, 2});
    REQUIRE(m.groundedAction.preconditions == expectedPrecons);
    REQUIRE(m.groundedAction.effects == expectedEffects);
}

TEST_CASE(TAG + "precon - positive eff (reverse order)") {
    std::vector<PDDL::ActionInstance> actions;
    PDDL::Action _act1 = PDDL::Action(
        "testaction1",
        std::vector<std::string> {"?x", "?y"},
        std::vector<PDDL::Literal> {PDDL::Literal(2, std::vector<unsigned int> {1}, true)},
        std::vector<PDDL::Literal> {PDDL::Literal(1, std::vector<unsigned int> {0}, true)}
    );
    PDDL::Action _act2 = PDDL::Action(
        "testaction2",
        std::vector<std::string> {"?x", "?y"},
        std::vector<PDDL::Literal> {PDDL::Literal(3, std::vector<unsigned int> {1}, true)},
        std::vector<PDDL::Literal> {PDDL::Literal(2, std::vector<unsigned int> {0}, true)}
    );
    PDDL::ActionInstance act1 = PDDL::ActionInstance(&_act1, std::vector<unsigned int> {0, 1});
    PDDL::ActionInstance act2 = PDDL::ActionInstance(&_act2, std::vector<unsigned int> {1, 2});

    actions.push_back(act1);
    actions.push_back(act2);

    // generate macro
    MacroGenerator macroGenerator = MacroGenerator();
    Macro m = macroGenerator.GenerateMacro(&actions);
    // expected stuff
    // nothing should be removed
    std::unordered_map<GroundedLiteral, bool> expectedPrecons ({
        {GroundedLiteral(2, std::vector<unsigned int> {1}), true},
        {GroundedLiteral(3, std::vector<unsigned int> {2}), true}
    });
    std::unordered_map<GroundedLiteral, bool> expectedEffects ({
        {GroundedLiteral(2, std::vector<unsigned int> {1}), true},
        {GroundedLiteral(1, std::vector<unsigned int> {0}), true}
    });
    REQUIRE(m.groundedAction.parameters == std::unordered_set<unsigned int> {0, 1, 2});
    REQUIRE(m.groundedAction.preconditions == expectedPrecons);
    REQUIRE(m.groundedAction.effects == expectedEffects);
}

TEST_CASE(TAG + "positive - negative eff") {
    std::vector<PDDL::ActionInstance> actions;
    PDDL::Action _act1 = PDDL::Action(
        "testaction1",
        std::vector<std::string> {"?x", "?y"},
        std::vector<PDDL::Literal> {PDDL::Literal(1, std::vector<unsigned int> {0}, true)},
        std::vector<PDDL::Literal> {PDDL::Literal(2, std::vector<unsigned int> {1}, true), PDDL::Literal(3, std::vector<unsigned int> {1}, true)}
    );
    PDDL::Action _act2 = PDDL::Action(
        "testaction2",
        std::vector<std::string> {"?x", "?y"},
        std::vector<PDDL::Literal> {PDDL::Literal(1, std::vector<unsigned int> {1}, true)},
        // the first effect here removes the 2nd effect from action above, the 2nd is same as first above, 3rd is added on top
        std::vector<PDDL::Literal> {PDDL::Literal(3, std::vector<unsigned int> {0}, false), PDDL::Literal(2, std::vector<unsigned int> {0}, true), PDDL::Literal(4, std::vector<unsigned int> {1}, true)}
    );
    PDDL::ActionInstance act1 = PDDL::ActionInstance(&_act1, std::vector<unsigned int> {0, 1});
    PDDL::ActionInstance act2 = PDDL::ActionInstance(&_act2, std::vector<unsigned int> {1, 2});
    
    actions.push_back(act1);
    actions.push_back(act2);

    // generate macro
    MacroGenerator macroGenerator = MacroGenerator();
    Macro m = macroGenerator.GenerateMacro(&actions);
    // expected stuff
    std::unordered_map<GroundedLiteral, bool> expectedPrecons ({
        {GroundedLiteral(1, std::vector<unsigned int> {0}), true},
        {GroundedLiteral(1, std::vector<unsigned int> {2}), true}
    });
    std::unordered_map<GroundedLiteral, bool> expectedEffects ({
        {GroundedLiteral(2, std::vector<unsigned int> {1}), true},
        // predicate 3, true should be absent
        {GroundedLiteral(3, std::vector<unsigned int> {1}), false},
        {GroundedLiteral(4, std::vector<unsigned int> {2}), true}
    });
    REQUIRE(m.groundedAction.parameters == std::unordered_set<unsigned int> {0, 1, 2});
    REQUIRE(m.groundedAction.preconditions == expectedPrecons);
    REQUIRE(m.groundedAction.effects == expectedEffects);
}

TEST_CASE(TAG + "negative - positive eff") {
    std::vector<PDDL::ActionInstance> actions;
    PDDL::Action _act1 = PDDL::Action(
        "testaction1",
        std::vector<std::string> {"?x", "?y"},
        std::vector<PDDL::Literal> {PDDL::Literal(1, std::vector<unsigned int> {0}, true)},
        std::vector<PDDL::Literal> {PDDL::Literal(2, std::vector<unsigned int> {1}, false), PDDL::Literal(3, std::vector<unsigned int> {1}, false)}
    );
    PDDL::Action _act2 = PDDL::Action(
        "testaction2",
        std::vector<std::string> {"?x", "?y"},
        std::vector<PDDL::Literal> {PDDL::Literal(1, std::vector<unsigned int> {1}, true)},
        // the first effect here removes the 2nd effect from action above, the 2nd is same as first above, 3rd is added on top
        std::vector<PDDL::Literal> {PDDL::Literal(3, std::vector<unsigned int> {0}, true), PDDL::Literal(2, std::vector<unsigned int> {0}, false), PDDL::Literal(4, std::vector<unsigned int> {1}, false)}
    );
    PDDL::ActionInstance act1 = PDDL::ActionInstance(&_act1, std::vector<unsigned int> {0, 1});
    PDDL::ActionInstance act2 = PDDL::ActionInstance(&_act2, std::vector<unsigned int> {1, 2});
    
    actions.push_back(act1);
    actions.push_back(act2);

    // generate macro
    MacroGenerator macroGenerator = MacroGenerator();
    Macro m = macroGenerator.GenerateMacro(&actions);
    // expected stuff
    std::unordered_map<GroundedLiteral, bool> expectedPrecons ({
        {GroundedLiteral(1, std::vector<unsigned int> {0}), true},
        {GroundedLiteral(1, std::vector<unsigned int> {2}), true}
    });
    std::unordered_map<GroundedLiteral, bool> expectedEffects ({
        {GroundedLiteral(2, std::vector<unsigned int> {1}), false},
        // predicate 3, false should be absent
        {GroundedLiteral(3, std::vector<unsigned int> {1}), true},
        {GroundedLiteral(4, std::vector<unsigned int> {2}), false},
    });
    REQUIRE(m.groundedAction.parameters == std::unordered_set<unsigned int> {0, 1, 2});
    REQUIRE(m.groundedAction.preconditions == expectedPrecons);
    REQUIRE(m.groundedAction.effects == expectedEffects);
}

TEST_CASE(TAG + "3 action blocks macro") {
    std::vector<PDDL::ActionInstance> actions;
    // predicates:
    // (on ?x ?y)
    // (ontable ?x)
    // (clear ?x)
    // (handempty)
    // (holding ?x)

    // example macro, not necessarily a good one
    // actions: pickup 0, stack 0 on 1, pickup 2
    PDDL::Action _act1 = PDDL::Action(
        "pickup",
        std::vector<std::string> {"?x"},
        // (clear ?x) (ontable ?x) (handempty)
        std::vector<PDDL::Literal> {PDDL::Literal(3, std::vector<unsigned int> {0}, true), PDDL::Literal(2, std::vector<unsigned int> {0}, true), PDDL::Literal(4, std::vector<unsigned int> {}, true)},
        // (not (ontable ?x)) (not (clear ?x)) (not (handempty)) (holding ?x)))
        std::vector<PDDL::Literal> {PDDL::Literal(2, std::vector<unsigned int> {0}, false), PDDL::Literal(3, std::vector<unsigned int> {0}, false), PDDL::Literal(4, std::vector<unsigned int> {}, false), PDDL::Literal(5, std::vector<unsigned int> {0}, true)}
    );
    PDDL::Action _act2 = PDDL::Action(
        "stack",
        std::vector<std::string> {"?x", "?y"},
        // (holding ?x) (clear ?y)
        std::vector<PDDL::Literal> {PDDL::Literal(5, std::vector<unsigned int> {0}, true), PDDL::Literal(3, std::vector<unsigned int> {1}, true)},
        // (not (holding ?x)) (not (clear ?y)) (clear ?x) (handempty) (on ?x ?y)))
        std::vector<PDDL::Literal> {PDDL::Literal(5, std::vector<unsigned int> {0}, false), PDDL::Literal(3, std::vector<unsigned int> {1}, false), PDDL::Literal(3, std::vector<unsigned int> {0}, true), PDDL::Literal(4, std::vector<unsigned int> {}, true), PDDL::Literal(1, std::vector<unsigned int> {0, 1}, true)}
    );

    PDDL::ActionInstance act1 = PDDL::ActionInstance(&_act1, std::vector<unsigned int> {0});
    PDDL::ActionInstance act2 = PDDL::ActionInstance(&_act2, std::vector<unsigned int> {0, 1});
    PDDL::ActionInstance act3 = PDDL::ActionInstance(&_act1, std::vector<unsigned int> {2});

    actions.push_back(act1);
    actions.push_back(act2);
    actions.push_back(act3);

    // generate macro
    MacroGenerator macroGenerator = MacroGenerator();
    Macro m = macroGenerator.GenerateMacro(&actions);

    // expected stuff
    std::unordered_map<GroundedLiteral, bool> expectedPrecons ({
        // ({3(0), 2(0), 4} U ({5(0), 3(1)} - {5(0)})) U ({3(2), 2(2), 4} - {3(0), 4, 1(0, 1)})
        // = 3(0), 2(0), 4, 3(1), 3(2), 2(2))
        {GroundedLiteral(3, std::vector<unsigned int> {0}), true},
        {GroundedLiteral(2, std::vector<unsigned int> {0}), true},
        {GroundedLiteral(4, std::vector<unsigned int> { }), true},
        {GroundedLiteral(3, std::vector<unsigned int> {1}), true},
        {GroundedLiteral(3, std::vector<unsigned int> {2}), true},
        {GroundedLiteral(2, std::vector<unsigned int> {2}), true}
    });
    std::unordered_map<GroundedLiteral, bool> expectedEffects ({
        // positive effects
        // ({5(0)} - {5(0), 3(1)}) U {3(0), 4, 1(0, 1)}
        // ({3(0), 4, 1(0, 1)} - {2(2), 3(2), 4}) U 5(2)
        // = 3(0), 1(0, 1), 5(2)
        {GroundedLiteral(3, std::vector<unsigned int> {0}), true},
        {GroundedLiteral(1, std::vector<unsigned int> {0, 1}), true},
        {GroundedLiteral(5, std::vector<unsigned int> {2}), true},
        // negative effects
        // ({2(0), 3(0), 4} - {4, 1(0, 1), 3(0)}) U {5(0), 3(1)}
        // ({2(0), 5(0), 3(1)} - {5(1)}) U {2(2), 3(2), 4}
        // = 2(0) 5(0), 3(1), 2(2), 3(2), 4
        {GroundedLiteral(2, std::vector<unsigned int> {0}), false},
        {GroundedLiteral(5, std::vector<unsigned int> {0}), false},
        {GroundedLiteral(3, std::vector<unsigned int> {1}), false},
        {GroundedLiteral(2, std::vector<unsigned int> {2}), false},
        {GroundedLiteral(3, std::vector<unsigned int> {2}), false},
        {GroundedLiteral(4, std::vector<unsigned int> { }), false}
    });

    REQUIRE(m.groundedAction.parameters == std::unordered_set<unsigned int> {0, 1, 2});
    REQUIRE(m.groundedAction.preconditions == expectedPrecons);
    REQUIRE(m.groundedAction.effects == expectedEffects);
}