#include <catch2/catch_test_macros.hpp>
#include <string>
#include <unordered_set>

using namespace std;

#include "../../src/Macros/Generators/Generator.hh"

const string TAG = "Macro ";

TEST_CASE(TAG + "two same simple actions") {
    vector<PDDLActionInstance> actions;
    // set up simple action with 1 precondition and 1 effect
    PDDLAction _act = PDDLAction(
        "testaction",
        vector<string> {"?x", "?y"},
        vector<PDDLLiteral> {PDDLLiteral(1, vector<unsigned int> {0}, true)},
        vector<PDDLLiteral> {PDDLLiteral(2, vector<unsigned int> {1}, true)}
    );
    PDDLActionInstance act1 = PDDLActionInstance(&_act, vector<unsigned int> {0, 1});
    PDDLActionInstance act2 = PDDLActionInstance(&_act, vector<unsigned int> {0, 1});
    actions.push_back(act1);
    actions.push_back(act2);
    // generate macro
    Macros::Generator macroGenerator = Macros::Generator();
    Macros::Macro m = macroGenerator.GenerateMacro(&actions);
    // expected stuff
    unordered_map<Macros::GroundedLiteral, bool> expectedPrecons {
        {Macros::GroundedLiteral(1, vector<unsigned int> {0}), true}
    };
    unordered_map<Macros::GroundedLiteral, bool> expectedEffects {
        {Macros::GroundedLiteral(2, vector<unsigned int> {1}), true}
    };
    REQUIRE(m.groundedAction.parameters == unordered_set<unsigned int> {0, 1});
    REQUIRE(m.groundedAction.preconditions == expectedPrecons);
    REQUIRE(m.groundedAction.effects == expectedEffects);
}

TEST_CASE(TAG + "two different simple actions") {
    vector<PDDLActionInstance> actions;
    PDDLAction _act1 = PDDLAction(
        "testaction1",
        vector<string> {"?x", "?y"},
        vector<PDDLLiteral> {PDDLLiteral(1, vector<unsigned int> {0}, true)},
        vector<PDDLLiteral> {PDDLLiteral(2, vector<unsigned int> {1}, true)}
    );
    PDDLAction _act2 = PDDLAction(
        "testaction2",
        vector<string> {"?x", "?y"},
        vector<PDDLLiteral> {PDDLLiteral(3, vector<unsigned int> {0}, false)},
        vector<PDDLLiteral> {PDDLLiteral(4, vector<unsigned int> {1}, true)}
    );
    PDDLActionInstance act1 = PDDLActionInstance(&_act1, vector<unsigned int> {0, 1});
    PDDLActionInstance act2 = PDDLActionInstance(&_act2, vector<unsigned int> {1, 3});
    actions.push_back(act1);
    actions.push_back(act2);
    // generate macro
    Macros::Generator macroGenerator = Macros::Generator();
    Macros::Macro m = macroGenerator.GenerateMacro(&actions);
    // expected stuff
    unordered_map<Macros::GroundedLiteral, bool> expectedPrecons {
        {Macros::GroundedLiteral(1, vector<unsigned int> {0}), true},
        {Macros::GroundedLiteral(3, vector<unsigned int> {1}), false}
    };
    unordered_map<Macros::GroundedLiteral, bool> expectedEffects {
        {Macros::GroundedLiteral(2, vector<unsigned int> {1}), true},
        {Macros::GroundedLiteral(4, vector<unsigned int> {3}), true}
    };
    REQUIRE(m.groundedAction.parameters == unordered_set<unsigned int> {0, 1, 3});
    REQUIRE(m.groundedAction.preconditions == expectedPrecons);
    REQUIRE(m.groundedAction.effects == expectedEffects);
}

TEST_CASE(TAG + "precon - positive eff") {
    vector<PDDLActionInstance> actions;
    PDDLAction _act1 = PDDLAction(
        "testaction1",
        vector<string> {"?x", "?y"},
        vector<PDDLLiteral> {PDDLLiteral(1, vector<unsigned int> {0}, true)},
        vector<PDDLLiteral> {PDDLLiteral(2, vector<unsigned int> {1}, true)}
    );
    PDDLAction _act2 = PDDLAction(
        "testaction2",
        vector<string> {"?x", "?y"},
        vector<PDDLLiteral> {PDDLLiteral(2, vector<unsigned int> {0}, true)},
        vector<PDDLLiteral> {PDDLLiteral(4, vector<unsigned int> {1}, true)}
    );
    PDDLActionInstance act1 = PDDLActionInstance(&_act1, vector<unsigned int> {0, 1});
    PDDLActionInstance act2 = PDDLActionInstance(&_act2, vector<unsigned int> {1, 2});

    actions.push_back(act1);
    actions.push_back(act2);

    // generate macro
    Macros::Generator macroGenerator = Macros::Generator();
    Macros::Macro m = macroGenerator.GenerateMacro(&actions);
    // expected stuff
    unordered_map<Macros::GroundedLiteral, bool> expectedPrecons {
        {Macros::GroundedLiteral(1, vector<unsigned int> {0}), true}
        // pddlliteral with predicate 2 should be absent
    };
    unordered_map<Macros::GroundedLiteral, bool> expectedEffects {
        {Macros::GroundedLiteral(2, vector<unsigned int> {1}), true},
        {Macros::GroundedLiteral(4, vector<unsigned int> {2}), true}
    };
    REQUIRE(m.groundedAction.parameters == unordered_set<unsigned int> {0, 1, 2});
    REQUIRE(m.groundedAction.preconditions == expectedPrecons);
    REQUIRE(m.groundedAction.effects == expectedEffects);
}

TEST_CASE(TAG + "precon - positive eff (reverse order)") {
    vector<PDDLActionInstance> actions;
    PDDLAction _act1 = PDDLAction(
        "testaction1",
        vector<string> {"?x", "?y"},
        vector<PDDLLiteral> {PDDLLiteral(2, vector<unsigned int> {1}, true)},
        vector<PDDLLiteral> {PDDLLiteral(1, vector<unsigned int> {0}, true)}
    );
    PDDLAction _act2 = PDDLAction(
        "testaction2",
        vector<string> {"?x", "?y"},
        vector<PDDLLiteral> {PDDLLiteral(3, vector<unsigned int> {1}, true)},
        vector<PDDLLiteral> {PDDLLiteral(2, vector<unsigned int> {0}, true)}
    );
    PDDLActionInstance act1 = PDDLActionInstance(&_act1, vector<unsigned int> {0, 1});
    PDDLActionInstance act2 = PDDLActionInstance(&_act2, vector<unsigned int> {1, 2});

    actions.push_back(act1);
    actions.push_back(act2);

    // generate macro
    Macros::Generator macroGenerator = Macros::Generator();
    Macros::Macro m = macroGenerator.GenerateMacro(&actions);
    // expected stuff
    // nothing should be removed
    unordered_map<Macros::GroundedLiteral, bool> expectedPrecons {
        {Macros::GroundedLiteral(2, vector<unsigned int> {1}), true},
        {Macros::GroundedLiteral(3, vector<unsigned int> {2}), true}
    };
    unordered_map<Macros::GroundedLiteral, bool> expectedEffects {
        {Macros::GroundedLiteral(2, vector<unsigned int> {1}), true},
        {Macros::GroundedLiteral(1, vector<unsigned int> {0}), true}
    };
    REQUIRE(m.groundedAction.parameters == unordered_set<unsigned int> {0, 1, 2});
    REQUIRE(m.groundedAction.preconditions == expectedPrecons);
    REQUIRE(m.groundedAction.effects == expectedEffects);
}

TEST_CASE(TAG + "positive - negative eff") {
    vector<PDDLActionInstance> actions;
    PDDLAction _act1 = PDDLAction(
        "testaction1",
        vector<string> {"?x", "?y"},
        vector<PDDLLiteral> {PDDLLiteral(1, vector<unsigned int> {0}, true)},
        vector<PDDLLiteral> {PDDLLiteral(2, vector<unsigned int> {1}, true), PDDLLiteral(3, vector<unsigned int> {1}, true)}
    );
    PDDLAction _act2 = PDDLAction(
        "testaction2",
        vector<string> {"?x", "?y"},
        vector<PDDLLiteral> {PDDLLiteral(1, vector<unsigned int> {1}, true)},
        // the first effect here removes the 2nd effect from action above, the 2nd is same as first above, 3rd is added on top
        vector<PDDLLiteral> {PDDLLiteral(3, vector<unsigned int> {0}, false), PDDLLiteral(2, vector<unsigned int> {0}, true), PDDLLiteral(4, vector<unsigned int> {1}, true)}
    );
    PDDLActionInstance act1 = PDDLActionInstance(&_act1, vector<unsigned int> {0, 1});
    PDDLActionInstance act2 = PDDLActionInstance(&_act2, vector<unsigned int> {1, 2});
    
    actions.push_back(act1);
    actions.push_back(act2);

    // generate macro
    Macros::Generator macroGenerator = Macros::Generator();
    Macros::Macro m = macroGenerator.GenerateMacro(&actions);
    // expected stuff
    unordered_map<Macros::GroundedLiteral, bool> expectedPrecons {
        {Macros::GroundedLiteral(1, vector<unsigned int> {0}), true},
        {Macros::GroundedLiteral(1, vector<unsigned int> {2}), true}
    };
    unordered_map<Macros::GroundedLiteral, bool> expectedEffects {
        {Macros::GroundedLiteral(2, vector<unsigned int> {1}), true},
        // predicate 3, true should be absent
        {Macros::GroundedLiteral(3, vector<unsigned int> {1}), false},
        {Macros::GroundedLiteral(4, vector<unsigned int> {2}), true}
    };
    REQUIRE(m.groundedAction.parameters == unordered_set<unsigned int> {0, 1, 2});
    REQUIRE(m.groundedAction.preconditions == expectedPrecons);
    REQUIRE(m.groundedAction.effects == expectedEffects);
}

TEST_CASE(TAG + "negative - positive eff") {
    vector<PDDLActionInstance> actions;
    PDDLAction _act1 = PDDLAction(
        "testaction1",
        vector<string> {"?x", "?y"},
        vector<PDDLLiteral> {PDDLLiteral(1, vector<unsigned int> {0}, true)},
        vector<PDDLLiteral> {PDDLLiteral(2, vector<unsigned int> {1}, false), PDDLLiteral(3, vector<unsigned int> {1}, false)}
    );
    PDDLAction _act2 = PDDLAction(
        "testaction2",
        vector<string> {"?x", "?y"},
        vector<PDDLLiteral> {PDDLLiteral(1, vector<unsigned int> {1}, true)},
        // the first effect here removes the 2nd effect from action above, the 2nd is same as first above, 3rd is added on top
        vector<PDDLLiteral> {PDDLLiteral(3, vector<unsigned int> {0}, true), PDDLLiteral(2, vector<unsigned int> {0}, false), PDDLLiteral(4, vector<unsigned int> {1}, false)}
    );
    PDDLActionInstance act1 = PDDLActionInstance(&_act1, vector<unsigned int> {0, 1});
    PDDLActionInstance act2 = PDDLActionInstance(&_act2, vector<unsigned int> {1, 2});
    
    actions.push_back(act1);
    actions.push_back(act2);

    // generate macro
    Macros::Generator macroGenerator = Macros::Generator();
    Macros::Macro m = macroGenerator.GenerateMacro(&actions);
    // expected stuff
    unordered_map<Macros::GroundedLiteral, bool> expectedPrecons {
        {Macros::GroundedLiteral(1, vector<unsigned int> {0}), true},
        {Macros::GroundedLiteral(1, vector<unsigned int> {2}), true}
    };
    unordered_map<Macros::GroundedLiteral, bool> expectedEffects {
        {Macros::GroundedLiteral(2, vector<unsigned int> {1}), false},
        // predicate 3, false should be absent
        {Macros::GroundedLiteral(3, vector<unsigned int> {1}), true},
        {Macros::GroundedLiteral(4, vector<unsigned int> {2}), false},
    };
    REQUIRE(m.groundedAction.parameters == unordered_set<unsigned int> {0, 1, 2});
    REQUIRE(m.groundedAction.preconditions == expectedPrecons);
    REQUIRE(m.groundedAction.effects == expectedEffects);
}

TEST_CASE(TAG + "3 action blocks macro") {
    vector<PDDLActionInstance> actions;
    // predicates:
    // (on ?x ?y)
    // (ontable ?x)
    // (clear ?x)
    // (handempty)
    // (holding ?x)

    // example macro, not necessarily a good one
    // actions: pickup 0, stack 0 on 1, pickup 2
    PDDLAction _act1 = PDDLAction(
        "pickup",
        vector<string> {"?x"},
        // (clear ?x) (ontable ?x) (handempty)
        vector<PDDLLiteral> {PDDLLiteral(3, vector<unsigned int> {0}, true), PDDLLiteral(2, vector<unsigned int> {0}, true), PDDLLiteral(4, vector<unsigned int> {}, true)},
        // (not (ontable ?x)) (not (clear ?x)) (not (handempty)) (holding ?x)))
        vector<PDDLLiteral> {PDDLLiteral(2, vector<unsigned int> {0}, false), PDDLLiteral(3, vector<unsigned int> {0}, false), PDDLLiteral(4, vector<unsigned int> {}, false), PDDLLiteral(5, vector<unsigned int> {0}, true)}
    );
    PDDLAction _act2 = PDDLAction(
        "stack",
        vector<string> {"?x", "?y"},
        // (holding ?x) (clear ?y)
        vector<PDDLLiteral> {PDDLLiteral(5, vector<unsigned int> {0}, true), PDDLLiteral(3, vector<unsigned int> {1}, true)},
        // (not (holding ?x)) (not (clear ?y)) (clear ?x) (handempty) (on ?x ?y)))
        vector<PDDLLiteral> {PDDLLiteral(5, vector<unsigned int> {0}, false), PDDLLiteral(3, vector<unsigned int> {1}, false), PDDLLiteral(3, vector<unsigned int> {0}, true), PDDLLiteral(4, vector<unsigned int> {}, true), PDDLLiteral(1, vector<unsigned int> {0, 1}, true)}
    );

    PDDLActionInstance act1 = PDDLActionInstance(&_act1, vector<unsigned int> {0});
    PDDLActionInstance act2 = PDDLActionInstance(&_act2, vector<unsigned int> {0, 1});
    PDDLActionInstance act3 = PDDLActionInstance(&_act1, vector<unsigned int> {2});

    actions.push_back(act1);
    actions.push_back(act2);
    actions.push_back(act3);

    // generate macro
    Macros::Generator macroGenerator = Macros::Generator();
    Macros::Macro m = macroGenerator.GenerateMacro(&actions);

    // expected stuff
    unordered_map<Macros::GroundedLiteral, bool> expectedPrecons {
        // ({3(0), 2(0), 4} U ({5(0), 3(1)} - {5(0)})) U ({3(2), 2(2), 4} - {3(0), 4, 1(0, 1)})
        // = 3(0), 2(0), 4, 3(1), 3(2), 2(2))
        {Macros::GroundedLiteral(3, vector<unsigned int> {0}), true},
        {Macros::GroundedLiteral(2, vector<unsigned int> {0}), true},
        {Macros::GroundedLiteral(4, vector<unsigned int> { }), true},
        {Macros::GroundedLiteral(3, vector<unsigned int> {1}), true},
        {Macros::GroundedLiteral(3, vector<unsigned int> {2}), true},
        {Macros::GroundedLiteral(2, vector<unsigned int> {2}), true}
    };
    unordered_map<Macros::GroundedLiteral, bool> expectedEffects {
        // positive effects
        // ({5(0)} - {5(0), 3(1)}) U {3(0), 4, 1(0, 1)}
        // ({3(0), 4, 1(0, 1)} - {2(2), 3(2), 4}) U 5(2)
        // = 3(0), 1(0, 1), 5(2)
        {Macros::GroundedLiteral(3, vector<unsigned int> {0}), true},
        {Macros::GroundedLiteral(1, vector<unsigned int> {0, 1}), true},
        {Macros::GroundedLiteral(5, vector<unsigned int> {2}), true},
        // negative effects
        // ({2(0), 3(0), 4} - {4, 1(0, 1), 3(0)}) U {5(0), 3(1)}
        // ({2(0), 5(0), 3(1)} - {5(1)}) U {2(2), 3(2), 4}
        // = 2(0) 5(0), 3(1), 2(2), 3(2), 4
        {Macros::GroundedLiteral(2, vector<unsigned int> {0}), false},
        {Macros::GroundedLiteral(5, vector<unsigned int> {0}), false},
        {Macros::GroundedLiteral(3, vector<unsigned int> {1}), false},
        {Macros::GroundedLiteral(2, vector<unsigned int> {2}), false},
        {Macros::GroundedLiteral(3, vector<unsigned int> {2}), false},
        {Macros::GroundedLiteral(4, vector<unsigned int> { }), false}
    };

    REQUIRE(m.groundedAction.parameters == unordered_set<unsigned int> {0, 1, 2});
    REQUIRE(m.groundedAction.preconditions == expectedPrecons);
    REQUIRE(m.groundedAction.effects == expectedEffects);
}