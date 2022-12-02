#include <catch2/catch_test_macros.hpp>

#include "../../src/PDDL/Instance.hh"
#include "../../src/Walker/ActionGenerator.hpp"

const std::string TAG = "ActionGenerator ";
#pragma region GenerateActions
PDDL::Domain GenerateDomain(std::vector<PDDL::Action> actions = std::vector<PDDL::Action>()) {
    return PDDL::Domain("Test",
    std::vector<std::string>{},
    std::vector<PDDL::Predicate>{
        PDDL::Predicate("=", {}, 0),
        PDDL::Predicate("P1", { "?x" }, 1),
        PDDL::Predicate("P2", { "?x", "?y"}, 2),
        PDDL::Predicate("P3", { "?x", "?y", "?z"}, 3)
    },
    std::unordered_map<std::string, unsigned int> {
        {"=", 0},
        {"P1", 1},
        {"P2", 2},
        {"P3", 3}
    },
    actions);
}

PDDL::Problem GenerateProblem(std::unordered_map<unsigned int, std::unordered_set<unsigned int>> unaryFacts = std::unordered_map<unsigned int, std::unordered_set<unsigned int>> {}, 
std::unordered_map<unsigned int, std::unordered_set<std::pair<unsigned int, unsigned int>>> binaryFacts = std::unordered_map<unsigned int, std::unordered_set<std::pair<unsigned int, unsigned int>>> {}, 
PDDL::Domain *domain = nullptr, std::vector<std::string> objects = std::vector<std::string>()) {
    return PDDL::Problem("Test", 
    domain, 
    objects, 
    std::unordered_map<std::string, unsigned int>{}, 
    PDDL::State(unaryFacts, binaryFacts), 
    PDDL::State(unaryFacts, binaryFacts));
}

TEST_CASE(TAG + "GenerateActions Unary - 1 Legal") {
    PDDL::Domain domain = GenerateDomain(std::vector<PDDL::Action>{
        PDDL::Action("Action 1", 
        {"?x"}, 
        std::vector<PDDL::Literal>{
            PDDL::Literal(1, std::vector<unsigned int>{ 0 }, true)
        },
        std::vector<PDDL::Literal>{})
    });
    PDDL::Problem problem = GenerateProblem(std::unordered_map<unsigned int, std::unordered_set<unsigned int>>{
        { 1, { 0 } }
    }, std::unordered_map<unsigned int, std::unordered_set<std::pair<unsigned int, unsigned int>>>{

    }, &domain,
    std::vector<std::string> {
        "O1"
    });

    PDDL::Instance instance = PDDL::Instance(&domain, &problem);
    ActionGenerator AG = ActionGenerator(&instance.domain->actions, instance.problem->objects.size());
    std::vector<PDDL::ActionInstance> actions = AG.GenerateActions(&(instance.problem->initState));
    REQUIRE(1 == actions.size());
}

TEST_CASE(TAG + "GenerateActions Unary - 0 Legal") {
    PDDL::Domain domain = GenerateDomain(std::vector<PDDL::Action>{
        PDDL::Action("Action 1", 
        {"?x"}, 
        std::vector<PDDL::Literal>{
            PDDL::Literal(1, std::vector<unsigned int>{ 0 }, false)
        },
        std::vector<PDDL::Literal>{})
    });
    PDDL::Problem problem = GenerateProblem(std::unordered_map<unsigned int, std::unordered_set<unsigned int>>{
        { 1, { 0 } }
    }, std::unordered_map<unsigned int, std::unordered_set<std::pair<unsigned int, unsigned int>>>{

    }, &domain,
    std::vector<std::string> {
        "O1"
    });

    PDDL::Instance instance = PDDL::Instance(&domain, &problem);
    ActionGenerator AG = ActionGenerator(&instance.domain->actions, instance.problem->objects.size());
    std::vector<PDDL::ActionInstance> actions = AG.GenerateActions(&(instance.problem->initState));
    REQUIRE(0 == actions.size());
}

TEST_CASE(TAG + "GenerateActions Equal") {
    PDDL::Domain domain = GenerateDomain(std::vector<PDDL::Action>{
        PDDL::Action("Action 1", 
        {"?x", "?y"}, 
        std::vector<PDDL::Literal>{
            PDDL::Literal(0, std::vector<unsigned int>{ 0, 1 }, true)
        },
        std::vector<PDDL::Literal>{})
    });
    PDDL::Problem problem = GenerateProblem(std::unordered_map<unsigned int, std::unordered_set<unsigned int>>{
        
    }, std::unordered_map<unsigned int, std::unordered_set<std::pair<unsigned int, unsigned int>>>{

    }, &domain,
    std::vector<std::string> {
        "O1", "O2", "O3"
    });

    PDDL::Instance instance = PDDL::Instance(&domain, &problem);
    ActionGenerator AG = ActionGenerator(&instance.domain->actions, instance.problem->objects.size());
    std::vector<PDDL::ActionInstance> actions = AG.GenerateActions(&(instance.problem->initState));
    REQUIRE(3 == actions.size());
}

TEST_CASE(TAG + "GenerateActions Not Equal") {
    PDDL::Domain domain = GenerateDomain(std::vector<PDDL::Action>{
        PDDL::Action("Action 1", 
        {"?x", "?y"}, 
        std::vector<PDDL::Literal>{
            PDDL::Literal(0, std::vector<unsigned int>{ 0, 1 }, false)
        },
        std::vector<PDDL::Literal>{})
    });
    PDDL::Problem problem = GenerateProblem(std::unordered_map<unsigned int, std::unordered_set<unsigned int>>{
        
    }, std::unordered_map<unsigned int, std::unordered_set<std::pair<unsigned int, unsigned int>>>{

    }, &domain,
    std::vector<std::string> {
        "O1", "O2", "O3"
    });

    PDDL::Instance instance = PDDL::Instance(&domain, &problem);
    ActionGenerator AG = ActionGenerator(&instance.domain->actions, instance.problem->objects.size());
    std::vector<PDDL::ActionInstance> actions = AG.GenerateActions(&(instance.problem->initState));
    REQUIRE(6 == actions.size());
}

TEST_CASE(TAG + "GenerateActions Multi - 1 Legal") {
    PDDL::Domain domain = GenerateDomain(std::vector<PDDL::Action>{
        PDDL::Action("Action 1", 
        {"?x", "?y"}, 
        std::vector<PDDL::Literal>{
            PDDL::Literal(2, std::vector<unsigned int>{ 0, 1 }, true)
        },
        std::vector<PDDL::Literal>{})
    });
    PDDL::Problem problem = GenerateProblem(std::unordered_map<unsigned int, std::unordered_set<unsigned int>>{
        
    }, std::unordered_map<unsigned int, std::unordered_set<std::pair<unsigned int, unsigned int>>>{ 
        { 2, { std::make_pair(0, 1) } }
    }, &domain,
    std::vector<std::string> {
        "O1", "O2", "O3", "O4"
    });

    PDDL::Instance instance = PDDL::Instance(&domain, &problem);
    ActionGenerator AG = ActionGenerator(&instance.domain->actions, instance.problem->objects.size());
    std::vector<PDDL::ActionInstance> actions = AG.GenerateActions(&(instance.problem->initState));
    REQUIRE(1 == actions.size());
}

#pragma endregion GenerateActions
#pragma region GetCandidateObjects
TEST_CASE(TAG + "GetCandidateObjects") {
    //std::unordered_set<unsigned int> GetCandidateObjects(const std::unordered_set<const PDDL::Literal*> *literals, const PDDL::State *state) const;
    PDDL::Domain domain{"", {}, {
        PDDL::Predicate("a", {"?x"}, 1),
        PDDL::Predicate("b", {"?x"}, 1),
        PDDL::Predicate("c", {"?x"}, 1),
    }, {}, {
        PDDL::Action("", { "", "", "", "" }, {
            PDDL::Literal(0, {0}, true), 
            PDDL::Literal(1, {1}, false), 
            PDDL::Literal(2, {0}, true),
            PDDL::Literal(0, {2}, true),
            PDDL::Literal(2, {2}, true),
            PDDL::Literal(0, {3}, false),
            PDDL::Literal(1, {3}, true)
        }, {})
    }};
    PDDL::Problem problem{
        "", &domain, { "O1", "O2", "O3" }, {}, {}, {}
    };
    ActionGenerator actionGenerator = ActionGenerator(&domain.actions, problem.objects.size());

    SECTION("No Literals") {
        PDDL::State state{
            {}, {}
        };
        const PDDL::Action *action = &domain.actions.at(0);
        std::unordered_set<const PDDL::Literal*> *literals = new std::unordered_set<const PDDL::Literal*>();
        std::unordered_set<unsigned int> candidateObjects = actionGenerator.GetCandidateObjects(literals, &state);
        free(literals);
        REQUIRE(problem.objects.size() == candidateObjects.size());
    }

    SECTION("Single Fact") {
        PDDL::State state{
            { { 0, { 0 } }, { 1, { 1 } }, { 2, { 0, 2 }} }, {}
        };
        const PDDL::Action *action = &domain.actions.at(0);

        SECTION("True") {
            auto literals = &action->applicableUnaryLiterals.at(0);
            std::unordered_set<unsigned int> candidateObjects = actionGenerator.GetCandidateObjects(literals, &state);
            REQUIRE(candidateObjects.size() == 1);
        }
        
        SECTION("False") {
            auto literals = &action->applicableUnaryLiterals.at(1);
            std::unordered_set<unsigned int> candidateObjects = actionGenerator.GetCandidateObjects(literals, &state);
            REQUIRE(candidateObjects.size() == 2);
        }
    }

    SECTION("Multi Fact") {
        PDDL::State state{
            { { 0, { 0 } }, { 1, { 1 } }, { 2, { 0, 2 }} }, {}
        };
        const PDDL::Action *action = &domain.actions.at(0);

        SECTION("True") {
            auto literals = &action->applicableUnaryLiterals.at(2);
            std::unordered_set<unsigned int> candidateObjects = actionGenerator.GetCandidateObjects(literals, &state);
            REQUIRE(candidateObjects.size() == 1);
        }
        
        SECTION("False") {
            auto literals = &action->applicableUnaryLiterals.at(3);
            std::unordered_set<unsigned int> candidateObjects = actionGenerator.GetCandidateObjects(literals, &state);
            REQUIRE(candidateObjects.size() == 1);
        }
    }
}
#pragma endregion GetCandidateObjects