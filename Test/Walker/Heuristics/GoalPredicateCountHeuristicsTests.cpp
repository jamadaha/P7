#include <catch2/catch_test_macros.hpp>

#include "../../src/PDDL/State.hh"
#include "../../src/PDDL/Instance.hh"
#include "../../src/Walker/Heuristics/GoalPredicateCountHeuristic.hh"

using namespace std;

const string TAG = "Goal Predicate Count";

const vector<PDDL::Action> baseActions{
    PDDL::Action("actiona", {"x","y"}, {
            PDDL::Literal(0, {0}, true),
            PDDL::Literal(1, {1}, true)
        }, {
            PDDL::Literal(0, {0}, false),
            PDDL::Literal(1, {1}, true)
        }),
    PDDL::Action("actionb", {"x","y"}, {
            PDDL::Literal(0, {0}, true),
            PDDL::Literal(1, {1}, true)
        }, {
            PDDL::Literal(0, {0}, false)
        }),
    PDDL::Action("actionc", {"x","y"}, {
            PDDL::Literal(0, {0}, true)
        }, {
            PDDL::Literal(2, {0,1}, true)
        }),
    PDDL::Action("actiond", {"x","y"}, {
            PDDL::Literal(0, {0}, true)
        }, {
            PDDL::Literal(3, {1,0}, true)
        })
};

#pragma region Eval

TEST_CASE(TAG + "Eval - NoMatchingPredicates - Unary") {
    unordered_map<unsigned int, unordered_set<unsigned int>> goalUnaryFacts{
    };
    unordered_map<unsigned int, unordered_set<pair<unsigned int, unsigned int>>> goalBinaryFacts{
    };
    PDDL::State goalState(
        goalUnaryFacts,
        goalBinaryFacts
    );
    PDDL::State initState;

    PDDL::Domain domain;
    PDDL::Problem problem("Problem-A", &domain, {}, {}, initState, goalState);
    PDDL::Instance(&domain, &problem);

    vector<PDDL::ActionInstance> actionInstances{
        PDDL::ActionInstance(&baseActions.at(0), { 0,1 }),
        PDDL::ActionInstance(&baseActions.at(1), { 1,2 })
    };

    GoalPredicateCountHeuristic heuristic(&domain, &problem);

    REQUIRE(heuristic.Eval(&initState, &actionInstances.at(0)) == 0);
    REQUIRE(heuristic.Eval(&initState, &actionInstances.at(1)) == 0);
}

TEST_CASE(TAG + "Eval - NoMatchingPredicates - Binary") {
    unordered_map<unsigned int, unordered_set<unsigned int>> goalUnaryFacts{
    };
    unordered_map<unsigned int, unordered_set<pair<unsigned int, unsigned int>>> goalBinaryFacts{
    };
    PDDL::State goalState(
        goalUnaryFacts,
        goalBinaryFacts
    );
    PDDL::State initState;

    PDDL::Domain domain;
    PDDL::Problem problem("Problem-A", &domain, {}, {}, initState, goalState);
    PDDL::Instance(&domain, &problem);

    vector<PDDL::ActionInstance> actionInstances{
        PDDL::ActionInstance(&baseActions.at(2), { 3,4 }),
        PDDL::ActionInstance(&baseActions.at(3), { 4,5 })
    };

    GoalPredicateCountHeuristic heuristic(&domain, &problem);

    REQUIRE(heuristic.Eval(&initState, &actionInstances.at(0)) == 0);
    REQUIRE(heuristic.Eval(&initState, &actionInstances.at(1)) == 0);
}

TEST_CASE(TAG + "Eval - SingleMatchingPredicates - Unary") {
    unordered_map<unsigned int, unordered_set<unsigned int>> goalUnaryFacts{
        {1, {1}}
    };
    unordered_map<unsigned int, unordered_set<pair<unsigned int, unsigned int>>> goalBinaryFacts{
    };
    PDDL::State goalState(
        goalUnaryFacts,
        goalBinaryFacts
    );
    PDDL::State initState;

    PDDL::Domain domain;
    PDDL::Problem problem("Problem-A", &domain, {}, {}, initState, goalState);
    PDDL::Instance(&domain, &problem);

    vector<PDDL::ActionInstance> actionInstances{
        PDDL::ActionInstance(&baseActions.at(0), { 0,1 }),
        PDDL::ActionInstance(&baseActions.at(1), { 1,2 })
    };

    GoalPredicateCountHeuristic heuristic(&domain, &problem);

    REQUIRE(heuristic.Eval(&initState, &actionInstances.at(0)) == 1);
    REQUIRE(heuristic.Eval(&initState, &actionInstances.at(1)) == 0);
}

TEST_CASE(TAG + "Eval - SingleMatchingPredicates - Binary") {
    unordered_map<unsigned int, unordered_set<unsigned int>> goalUnaryFacts{
    };
    unordered_map<unsigned int, unordered_set<pair<unsigned int, unsigned int>>> goalBinaryFacts{
        {3, {make_pair(3,2)}}
    };
    PDDL::State goalState(
        goalUnaryFacts,
        goalBinaryFacts
    );
    PDDL::State initState;

    PDDL::Domain domain;
    PDDL::Problem problem("Problem-A", &domain, {}, {}, initState, goalState);
    PDDL::Instance(&domain, &problem);

    vector<PDDL::ActionInstance> actionInstances{
        PDDL::ActionInstance(&baseActions.at(2), { 0,1 }),
        PDDL::ActionInstance(&baseActions.at(3), { 2,3 })
    };

    GoalPredicateCountHeuristic heuristic(&domain, &problem);

    REQUIRE(heuristic.Eval(&initState, &actionInstances.at(0)) == 0);
    REQUIRE(heuristic.Eval(&initState, &actionInstances.at(1)) == 1);
}

TEST_CASE(TAG + "Eval - MultipleMatchingPredicates - Unary") {
    unordered_map<unsigned int, unordered_set<unsigned int>> goalUnaryFacts{
        {1, {1}},
        {0, {0}}
    };
    unordered_map<unsigned int, unordered_set<pair<unsigned int, unsigned int>>> goalBinaryFacts{
    };
    PDDL::State goalState(
        goalUnaryFacts,
        goalBinaryFacts
    );
    PDDL::State initState;

    PDDL::Domain domain;
    PDDL::Problem problem("Problem-A", &domain, {}, {}, initState, goalState);
    PDDL::Instance(&domain, &problem);

    vector<PDDL::ActionInstance> actionInstances{
        PDDL::ActionInstance(&baseActions.at(0), { 0,1 }),
        PDDL::ActionInstance(&baseActions.at(1), { 0,1 })
    };

    GoalPredicateCountHeuristic heuristic(&domain, &problem);

    REQUIRE(heuristic.Eval(&initState, &actionInstances.at(0)) == 1);
    REQUIRE(heuristic.Eval(&initState, &actionInstances.at(1)) == 0);
}

TEST_CASE(TAG + "Eval - MultipleMatchingPredicates - Binary") {
    unordered_map<unsigned int, unordered_set<unsigned int>> goalUnaryFacts{
    };
    unordered_map<unsigned int, unordered_set<pair<unsigned int, unsigned int>>> goalBinaryFacts{
        {2, {make_pair(2,3)}},
        {3, {make_pair(1,0)}}
    };
    PDDL::State goalState(
        goalUnaryFacts,
        goalBinaryFacts
    );
    PDDL::State initState;

    PDDL::Domain domain;
    PDDL::Problem problem("Problem-A", &domain, {}, {}, initState, goalState);
    PDDL::Instance(&domain, &problem);

    vector<PDDL::ActionInstance> actionInstances{
        PDDL::ActionInstance(&baseActions.at(2), { 2,3 }),
        PDDL::ActionInstance(&baseActions.at(3), { 0,1 })
    };

    GoalPredicateCountHeuristic heuristic(&domain, &problem);

    REQUIRE(heuristic.Eval(&initState, &actionInstances.at(0)) == 1);
    REQUIRE(heuristic.Eval(&initState, &actionInstances.at(1)) == 1);
}

#pragma endregion


#pragma region NextChoice

TEST_CASE(TAG + "NextChoice - SingleMatchingPredicates - Unary") {
    unordered_map<unsigned int, unordered_set<unsigned int>> goalUnaryFacts{
        {1, {1}}
    };
    unordered_map<unsigned int, unordered_set<pair<unsigned int, unsigned int>>> goalBinaryFacts{
    };
    PDDL::State goalState(
        goalUnaryFacts,
        goalBinaryFacts
    );
    PDDL::State initState;

    PDDL::Domain domain;
    PDDL::Problem problem("Problem-A", &domain, {}, {}, initState, goalState);
    PDDL::Instance(&domain, &problem);

    vector<PDDL::ActionInstance> actionInstances{
        PDDL::ActionInstance(&baseActions.at(0), { 0,1 }),
        PDDL::ActionInstance(&baseActions.at(1), { 1,2 })
    };

    GoalPredicateCountHeuristic heuristic(&domain, &problem);

    REQUIRE(heuristic.NextChoice(&initState, &actionInstances) == &actionInstances.at(0));
}


TEST_CASE(TAG + "NextChoice - SingleMatchingPredicates - Binary") {
    unordered_map<unsigned int, unordered_set<unsigned int>> goalUnaryFacts{
    };
    unordered_map<unsigned int, unordered_set<pair<unsigned int, unsigned int>>> goalBinaryFacts{
        {3, {make_pair(3,2)}}
    };
    PDDL::State goalState(
        goalUnaryFacts,
        goalBinaryFacts
    );
    PDDL::State initState;

    PDDL::Domain domain;
    PDDL::Problem problem("Problem-A", &domain, {}, {}, initState, goalState);
    PDDL::Instance(&domain, &problem);

    vector<PDDL::ActionInstance> actionInstances{
        PDDL::ActionInstance(&baseActions.at(2), { 0,1 }),
        PDDL::ActionInstance(&baseActions.at(3), { 2,3 })
    };

    GoalPredicateCountHeuristic heuristic(&domain, &problem);

    REQUIRE(heuristic.NextChoice(&initState, &actionInstances) == &actionInstances.at(1));
}

TEST_CASE(TAG + "NextChoice - MultipleMatchingPredicates - Unary") {
    unordered_map<unsigned int, unordered_set<unsigned int>> goalUnaryFacts{
        {1, {1}},
        {0, {0}}
    };
    unordered_map<unsigned int, unordered_set<pair<unsigned int, unsigned int>>> goalBinaryFacts{
    };
    PDDL::State goalState(
        goalUnaryFacts,
        goalBinaryFacts
    );
    PDDL::State initState;

    PDDL::Domain domain;
    PDDL::Problem problem("Problem-A", &domain, {}, {}, initState, goalState);
    PDDL::Instance(&domain, &problem);

    vector<PDDL::ActionInstance> actionInstances{
        PDDL::ActionInstance(&baseActions.at(1), { 0,1 }),
        PDDL::ActionInstance(&baseActions.at(0), { 0,1 })
    };

    GoalPredicateCountHeuristic heuristic(&domain, &problem);

    REQUIRE(heuristic.NextChoice(&initState, &actionInstances) == &actionInstances.at(1));
}

#pragma endregion
