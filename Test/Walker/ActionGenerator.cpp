#include <catch2/catch_test_macros.hpp>

#include "../../src/IntermediatePDDL/PDDLInstance.hh"
#include "../../src/Walker/ActionGenerator.hpp"

const std::string TAG = "ActionGenerator ";

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

PDDLProblem GenerateProblem(std::unordered_map<unsigned int, std::unordered_set<unsigned int>> unaryFacts = std::unordered_map<unsigned int, std::unordered_set<unsigned int>> {}, std::unordered_map<unsigned int, std::vector<MultiFact>> multiFacts = std::unordered_map<unsigned int, std::vector<MultiFact>> {}, 
PDDLDomain *domain = nullptr, std::vector<std::string> objects = std::vector<std::string>()) {
    return PDDLProblem("Test", 
    domain, 
    objects, 
    std::unordered_map<std::string, unsigned int>{}, 
    PDDLState(unaryFacts, multiFacts), 
    PDDLState(unaryFacts, multiFacts));
}

#pragma region GenerateActions

TEST_CASE(TAG + "Empty") {
    PDDLInstance instance = PDDLInstance(new PDDLDomain(), new PDDLProblem());
    ActionGenerator AG = ActionGenerator(instance.domain, instance.problem);
    std::vector<PDDLActionInstance> actions = AG.GenerateActions(&instance.problem->initState);
    REQUIRE(actions.size() == 0);
    free(instance.domain);
    free(instance.problem);
}

TEST_CASE(TAG + "Unary - 1 Legal") {
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
    }, std::unordered_map<unsigned int, std::vector<MultiFact>>{

    }, &domain,
    std::vector<std::string> {
        "O1"
    });

    PDDLInstance instance = PDDLInstance(&domain, &problem);
    ActionGenerator AG = ActionGenerator(instance.domain, instance.problem);
    std::vector<PDDLActionInstance> actions = AG.GenerateActions(&(instance.problem->initState));
    REQUIRE(1 == actions.size());
    REQUIRE("O1" == problem.objects.at(actions.at(0).objects.at(0)));
}

TEST_CASE(TAG + "Unary - 0 Legal") {
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
    }, std::unordered_map<unsigned int, std::vector<MultiFact>>{

    }, &domain,
    std::vector<std::string> {
        "O1"
    });

    PDDLInstance instance = PDDLInstance(&domain, &problem);
    ActionGenerator AG = ActionGenerator(instance.domain, instance.problem);
    std::vector<PDDLActionInstance> actions = AG.GenerateActions(&(instance.problem->initState));
    REQUIRE(0 == actions.size());
}

TEST_CASE(TAG + "Equal") {
    PDDLDomain domain = GenerateDomain(std::vector<PDDLAction>{
        PDDLAction("Action 1", 
        {"?x", "?y"}, 
        std::vector<PDDLLiteral>{
            PDDLLiteral(0, std::vector<unsigned int>{ 0, 1 }, true)
        },
        std::vector<PDDLLiteral>{})
    });
    PDDLProblem problem = GenerateProblem(std::unordered_map<unsigned int, std::unordered_set<unsigned int>>{
        
    }, std::unordered_map<unsigned int, std::vector<MultiFact>>{

    }, &domain,
    std::vector<std::string> {
        "O1", "O2", "O3"
    });

    PDDLInstance instance = PDDLInstance(&domain, &problem);
    ActionGenerator AG = ActionGenerator(instance.domain, instance.problem);
    std::vector<PDDLActionInstance> actions = AG.GenerateActions(&(instance.problem->initState));
    REQUIRE(3 == actions.size());
    for (int i = 0; i < 3; i++) {
        REQUIRE(2 == actions.at(i).objects.size());
        REQUIRE(actions.at(i).objects.at(0) == actions.at(i).objects.at(1));
    }
}

TEST_CASE(TAG + "Not Equal") {
    PDDLDomain domain = GenerateDomain(std::vector<PDDLAction>{
        PDDLAction("Action 1", 
        {"?x", "?y"}, 
        std::vector<PDDLLiteral>{
            PDDLLiteral(0, std::vector<unsigned int>{ 0, 1 }, false)
        },
        std::vector<PDDLLiteral>{})
    });
    PDDLProblem problem = GenerateProblem(std::unordered_map<unsigned int, std::unordered_set<unsigned int>>{
        
    }, std::unordered_map<unsigned int, std::vector<MultiFact>>{

    }, &domain,
    std::vector<std::string> {
        "O1", "O2", "O3"
    });

    PDDLInstance instance = PDDLInstance(&domain, &problem);
    ActionGenerator AG = ActionGenerator(instance.domain, instance.problem);
    std::vector<PDDLActionInstance> actions = AG.GenerateActions(&(instance.problem->initState));
    REQUIRE(6 == actions.size());
    for (int i = 0; i < actions.size(); i++) {
        REQUIRE(2 == actions.at(i).objects.size());
        REQUIRE(actions.at(i).objects.at(0) != actions.at(i).objects.at(1));
    }
}

TEST_CASE(TAG + "Multi - 1 Legal") {
    PDDLDomain domain = GenerateDomain(std::vector<PDDLAction>{
        PDDLAction("Action 1", 
        {"?x", "?y"}, 
        std::vector<PDDLLiteral>{
            PDDLLiteral(2, std::vector<unsigned int>{ 0, 1 }, true)
        },
        std::vector<PDDLLiteral>{})
    });
    PDDLProblem problem = GenerateProblem(std::unordered_map<unsigned int, std::unordered_set<unsigned int>>{
        
    }, std::unordered_map<unsigned int, std::vector<MultiFact>>{
        { 2, { MultiFact({0, 1} )} }
    }, &domain,
    std::vector<std::string> {
        "O1", "O2", "O3", "O4"
    });

    PDDLInstance instance = PDDLInstance(&domain, &problem);
    ActionGenerator AG = ActionGenerator(instance.domain, instance.problem);
    std::vector<PDDLActionInstance> actions = AG.GenerateActions(&(instance.problem->initState));
    REQUIRE(1 == actions.size());
    REQUIRE("O1" == problem.objects.at(actions.at(0).objects.at(0)));
    REQUIRE("O2" == problem.objects.at(actions.at(0).objects.at(1)));
}

#pragma endregion GenerateActions

