#include <catch2/catch_test_macros.hpp>

#include "../../src/IntermediatePDDL/PDDLState.hh"

const std::string TAG = "Walker ";

TEST_CASE(TAG + "DoAction Unary") {
    PDDLState state = PDDLState(
        std::unordered_map<unsigned int, std::unordered_set<unsigned int>>{
            {0, std::unordered_set<unsigned int>{ }},
            {1, std::unordered_set<unsigned int>{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }}
        },
        std::unordered_map<unsigned int, std::unordered_set<std::pair<unsigned int, unsigned int>>> {

        }
    );

    SECTION("Adding") {
        PDDLAction action = PDDLAction("Name",
        std::vector<std::string>{ "?x" },
        std::vector<PDDLLiteral>{},
        std::vector<PDDLLiteral>{
            PDDLLiteral(0, std::vector<unsigned int>{ 0 }, true),
            PDDLLiteral(1, std::vector<unsigned int>{ 0 }, true)
        });
        for (unsigned int i = 0; i < 10; i++) {
            // Check that state is as expected
            REQUIRE(!state.unaryFacts.at(0).contains(i));
            REQUIRE(state.unaryFacts.at(1).contains(i));
            PDDLActionInstance actionInstance = PDDLActionInstance(&action, std::vector<unsigned int>{ i });
            state.DoAction(&actionInstance);
            // Check that the state has been updated
            REQUIRE(state.unaryFacts.at(0).contains(i));
            REQUIRE(state.unaryFacts.at(1).contains(i));
            // Check that rest of state is unaffected
            for (int t = i - 1; t >= 0; t--) {
                REQUIRE(state.unaryFacts.at(0).contains(t));
                REQUIRE(state.unaryFacts.at(1).contains(t));
            }
            for (int t = i + 1; t < 10; t++) {
                REQUIRE(!state.unaryFacts.at(0).contains(t));
                REQUIRE(state.unaryFacts.at(1).contains(t));
            }
        }
    };

    SECTION("Subtracting") {
        PDDLAction action = PDDLAction("Name",
        std::vector<std::string>{ "?x" },
        std::vector<PDDLLiteral>{},
        std::vector<PDDLLiteral>{
            PDDLLiteral(0, std::vector<unsigned int>{ 0 }, false),
            PDDLLiteral(1, std::vector<unsigned int>{ 0 }, false)
        });
        for (unsigned int i = 0; i < 10; i++) {
            // Check that state is as expected
            REQUIRE(!state.unaryFacts.at(0).contains(i));
            REQUIRE(state.unaryFacts.at(1).contains(i));
            PDDLActionInstance actionInstance = PDDLActionInstance(&action, std::vector<unsigned int>{ i });
            state.DoAction(&actionInstance);
            // Check that the state has been updated
            REQUIRE(!state.unaryFacts.at(0).contains(i));
            REQUIRE(!state.unaryFacts.at(1).contains(i));
            // Check that rest of state is unaffected
            for (int t = i - 1; t >= 0; t--) {
                REQUIRE(!state.unaryFacts.at(0).contains(t));
                REQUIRE(!state.unaryFacts.at(1).contains(t));
            }
            for (int t = i + 1; t < 10; t++) {
                REQUIRE(!state.unaryFacts.at(0).contains(t));
                REQUIRE(state.unaryFacts.at(1).contains(t));
            }
        }
    };
}
