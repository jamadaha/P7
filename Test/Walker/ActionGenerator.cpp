#include <catch2/catch_test_macros.hpp>

#include "../../src/IntermediatePDDL/PDDLInstance.hh"
#include "../../src/Walker/ActionGenerator.hpp"

const std::string TAG = "ActionGenerator ";
#pragma region GenerateActions
PDDLDomain GenerateDomain(std::vector<PDDLAction> actions = std::vector<PDDLAction>()) {
    return PDDLDomain("Test",
    std::vector<std::string>{},
    std::vector<PDDLPredicate>{
        PDDLPredicate("=", 0),
        PDDLPredicate("P1", 1),
        PDDLPredicate("P2", 2),
        PDDLPredicate("P3", 3)
    },
    std::unordered_map<std::string, unsigned int> {
        {"=", 0},
        {"P1", 1},
        {"P2", 2},
        {"P3", 3}
    },
    actions);
}

PDDLProblem GenerateProblem(std::unordered_map<unsigned int, std::unordered_set<unsigned int>> unaryFacts = std::unordered_map<unsigned int, std::unordered_set<unsigned int>> {}, 
std::unordered_map<unsigned int, std::unordered_set<std::pair<unsigned int, unsigned int>>> binaryFacts = std::unordered_map<unsigned int, std::unordered_set<std::pair<unsigned int, unsigned int>>> {}, 
PDDLDomain *domain = nullptr, std::vector<std::string> objects = std::vector<std::string>()) {
    return PDDLProblem("Test", 
    domain, 
    objects, 
    std::unordered_map<std::string, unsigned int>{}, 
    PDDLState(unaryFacts, binaryFacts), 
    PDDLState(unaryFacts, binaryFacts));
}

TEST_CASE(TAG + "GenerateActions Empty") {
    PDDLInstance instance = PDDLInstance(new PDDLDomain(), new PDDLProblem());
    ActionGenerator AG = ActionGenerator(&instance.domain->actions, instance.problem->objects.size());
    std::vector<PDDLActionInstance> actions = AG.GenerateActions(&instance.problem->initState);
    REQUIRE(actions.size() == 0);
    free(instance.domain);
    free(instance.problem);
}

TEST_CASE(TAG + "GenerateActions Unary - 1 Legal") {
    PDDLDomain domain = GenerateDomain(std::vector<PDDLAction>{
        PDDLAction("Action 1", 
        {"?x"}, 
        std::vector<PDDLLiteral>{
            PDDLLiteral(1, std::vector<unsigned int>{ 0 }, true)
        },
        std::vector<PDDLLiteral>{})
    });
    PDDLProblem problem = GenerateProblem(std::unordered_map<unsigned int, std::unordered_set<unsigned int>>{
        { 1, { 0 } }
    }, std::unordered_map<unsigned int, std::unordered_set<std::pair<unsigned int, unsigned int>>>{

    }, &domain,
    std::vector<std::string> {
        "O1"
    });

    PDDLInstance instance = PDDLInstance(&domain, &problem);
    ActionGenerator AG = ActionGenerator(&instance.domain->actions, instance.problem->objects.size());
    std::vector<PDDLActionInstance> actions = AG.GenerateActions(&(instance.problem->initState));
    REQUIRE(1 == actions.size());
}

TEST_CASE(TAG + "GenerateActions Unary - 0 Legal") {
    PDDLDomain domain = GenerateDomain(std::vector<PDDLAction>{
        PDDLAction("Action 1", 
        {"?x"}, 
        std::vector<PDDLLiteral>{
            PDDLLiteral(1, std::vector<unsigned int>{ 0 }, false)
        },
        std::vector<PDDLLiteral>{})
    });
    PDDLProblem problem = GenerateProblem(std::unordered_map<unsigned int, std::unordered_set<unsigned int>>{
        { 1, { 0 } }
    }, std::unordered_map<unsigned int, std::unordered_set<std::pair<unsigned int, unsigned int>>>{

    }, &domain,
    std::vector<std::string> {
        "O1"
    });

    PDDLInstance instance = PDDLInstance(&domain, &problem);
    ActionGenerator AG = ActionGenerator(&instance.domain->actions, instance.problem->objects.size());
    std::vector<PDDLActionInstance> actions = AG.GenerateActions(&(instance.problem->initState));
    REQUIRE(0 == actions.size());
}

TEST_CASE(TAG + "GenerateActions Equal") {
    PDDLDomain domain = GenerateDomain(std::vector<PDDLAction>{
        PDDLAction("Action 1", 
        {"?x", "?y"}, 
        std::vector<PDDLLiteral>{
            PDDLLiteral(0, std::vector<unsigned int>{ 0, 1 }, true)
        },
        std::vector<PDDLLiteral>{})
    });
    PDDLProblem problem = GenerateProblem(std::unordered_map<unsigned int, std::unordered_set<unsigned int>>{
        
    }, std::unordered_map<unsigned int, std::unordered_set<std::pair<unsigned int, unsigned int>>>{

    }, &domain,
    std::vector<std::string> {
        "O1", "O2", "O3"
    });

    PDDLInstance instance = PDDLInstance(&domain, &problem);
    ActionGenerator AG = ActionGenerator(&instance.domain->actions, instance.problem->objects.size());
    std::vector<PDDLActionInstance> actions = AG.GenerateActions(&(instance.problem->initState));
    REQUIRE(3 == actions.size());
}

TEST_CASE(TAG + "GenerateActions Not Equal") {
    PDDLDomain domain = GenerateDomain(std::vector<PDDLAction>{
        PDDLAction("Action 1", 
        {"?x", "?y"}, 
        std::vector<PDDLLiteral>{
            PDDLLiteral(0, std::vector<unsigned int>{ 0, 1 }, false)
        },
        std::vector<PDDLLiteral>{})
    });
    PDDLProblem problem = GenerateProblem(std::unordered_map<unsigned int, std::unordered_set<unsigned int>>{
        
    }, std::unordered_map<unsigned int, std::unordered_set<std::pair<unsigned int, unsigned int>>>{

    }, &domain,
    std::vector<std::string> {
        "O1", "O2", "O3"
    });

    PDDLInstance instance = PDDLInstance(&domain, &problem);
    ActionGenerator AG = ActionGenerator(&instance.domain->actions, instance.problem->objects.size());
    std::vector<PDDLActionInstance> actions = AG.GenerateActions(&(instance.problem->initState));
    REQUIRE(6 == actions.size());
}

TEST_CASE(TAG + "GenerateActions Multi - 1 Legal") {
    PDDLDomain domain = GenerateDomain(std::vector<PDDLAction>{
        PDDLAction("Action 1", 
        {"?x", "?y"}, 
        std::vector<PDDLLiteral>{
            PDDLLiteral(2, std::vector<unsigned int>{ 0, 1 }, true)
        },
        std::vector<PDDLLiteral>{})
    });
    PDDLProblem problem = GenerateProblem(std::unordered_map<unsigned int, std::unordered_set<unsigned int>>{
        
    }, std::unordered_map<unsigned int, std::unordered_set<std::pair<unsigned int, unsigned int>>>{ 
        { 2, { std::make_pair(0, 1) } }
    }, &domain,
    std::vector<std::string> {
        "O1", "O2", "O3", "O4"
    });

    PDDLInstance instance = PDDLInstance(&domain, &problem);
    ActionGenerator AG = ActionGenerator(&instance.domain->actions, instance.problem->objects.size());
    std::vector<PDDLActionInstance> actions = AG.GenerateActions(&(instance.problem->initState));
    REQUIRE(1 == actions.size());
}

#pragma endregion GenerateActions
#pragma region GetCandidateObjects
TEST_CASE(TAG + "GetCandidateObjects") {
    //std::unordered_set<unsigned int> GetCandidateObjects(const std::unordered_set<const PDDLLiteral*> *literals, const PDDLState *state) const;
    PDDLDomain domain{"", {}, {
        PDDLPredicate(1),
        PDDLPredicate(1),
        PDDLPredicate(1)
    }, {}, {
        PDDLAction("", { "", "", "", "" }, {
            PDDLLiteral(0, {0}, true), 
            PDDLLiteral(1, {1}, false), 
            PDDLLiteral(2, {0}, true),
            PDDLLiteral(0, {2}, true),
            PDDLLiteral(2, {2}, true),
            PDDLLiteral(0, {3}, false),
            PDDLLiteral(1, {3}, true)
        }, {})
    }};
    PDDLProblem problem{
        "", &domain, { "O1", "O2", "O3" }, {}, {}, {}
    };
    ActionGenerator actionGenerator = ActionGenerator(&domain.actions, problem.objects.size());

    SECTION("No Literals") {
        PDDLState state{
            {}, {}
        };
        const PDDLAction *action = &domain.actions.at(0);
        std::unordered_set<const PDDLLiteral*> *literals = new std::unordered_set<const PDDLLiteral*>();
        std::unordered_set<unsigned int> candidateObjects = actionGenerator.GetCandidateObjects(literals, &state);
        free(literals);
        REQUIRE(problem.objects.size() == candidateObjects.size());
    }

    SECTION("Single Fact") {
        PDDLState state{
            { { 0, { 0 } }, { 1, { 1 } }, { 2, { 0, 2 }} }, {}
        };
        const PDDLAction *action = &domain.actions.at(0);

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
        PDDLState state{
            { { 0, { 0 } }, { 1, { 1 } }, { 2, { 0, 2 }} }, {}
        };
        const PDDLAction *action = &domain.actions.at(0);

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