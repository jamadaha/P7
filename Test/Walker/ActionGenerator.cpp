#include <catch2/catch_test_macros.hpp>

#include "../../src/IntermediatePDDL/PDDLInstance.hh"
#include "../../src/Walker/ActionGenerator.hpp"

const std::string TAG = "ActionGenerator ";

PDDLDomain GenerateDomain(std::vector<PDDLAction> actions = std::vector<PDDLAction>()) {
    return PDDLDomain("Test",
    std::vector<std::string>{},
    std::vector<PDDLPredicate>{
        PDDLPredicate("P1", 1),
        PDDLPredicate("P2", 2),
        PDDLPredicate("P3", 3)
    },
    std::unordered_map<std::string, unsigned int> {
        {"P1", 0},
        {"P2", 1},
        {"P3", 2}
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

//#pragma region Precondition

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
            PDDLLiteral(0, std::vector<unsigned int>{ 0 }, true)
        },
        std::vector<PDDLLiteral>{})
    });
    PDDLProblem problem = GenerateProblem(std::unordered_map<unsigned int, std::unordered_set<unsigned int>>{
        { 0, { 0 } }
    }, std::unordered_map<unsigned int, std::vector<MultiFact>>{

    }, &domain,
    std::vector<std::string> {
        "O1"
    });

    PDDLInstance instance = PDDLInstance(&domain, &problem);
    ActionGenerator AG = ActionGenerator(instance.domain, instance.problem);
    std::vector<PDDLActionInstance> actions = AG.GenerateActions(&(instance.problem->initState));
    REQUIRE(1 == actions.size());
}

TEST_CASE(TAG + "Unary - 0 Legal") {
    PDDLDomain domain = GenerateDomain(std::vector<PDDLAction>{
        PDDLAction("Action 1", 
        {"?x"}, 
        std::vector<PDDLLiteral>{
            PDDLLiteral(0, std::vector<unsigned int>{ 0 }, false)
        },
        std::vector<PDDLLiteral>{})
    });
    PDDLProblem problem = GenerateProblem(std::unordered_map<unsigned int, std::unordered_set<unsigned int>>{
        { 0, { 0 } }
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
/*
TEST_CASE(TAG + "Unary - 1 legal") {
    PDDLDomain domain = GenerateDomain();
    PDDLProblem problem = GenerateProblem(std::vector<std::string>{ "o1" });

    PDDLInstance instance = PDDLInstance(&domain, &problem);
    ActionGenerator AG = ActionGenerator(instance.domain);
    std::vector<PDDLActionInstance> actions = AG.GenerateActions(&(instance.problem->initState));
    REQUIRE(1 == actions.size());
}
/*
TEST_CASE(TAG + "Unary - 2 legal") {
    PDDLDomain domain = GenerateDomain();
    PDDLProblem problem = GenerateProblem(std::vector<std::string>{ "o1", "o2" });

    PDDLInstance instance = PDDLInstance(&domain, &problem);
    ActionGenerator AG = ActionGenerator(instance.domain);
    std::vector<PDDLActionInstance> actions = AG.GenerateActions(&(instance.problem->initState));
    REQUIRE(2 == actions.size());
}

TEST_CASE(TAG + "UnaryI - 0 legal") {
    PDDLDomain domain = GenerateDomain();
    PDDLProblem problem = GenerateProblem(std::vector<std::string>{ "o1" }, std::vector<PDDLPredicate>{
        PDDLPredicate("IsTrue", std::vector<PDDLArg>{ PDDLArg("o1", nullptr) })
    });

    PDDLInstance instance = PDDLInstance(&domain, &problem);
    ActionGenerator AG = ActionGenerator(instance.domain);
    std::vector<PDDLActionInstance> actions = AG.GenerateActions(&(instance.problem->initState));
    REQUIRE(0 == actions.size());
}

TEST_CASE(TAG + "UnaryI - 1 legal") {
    PDDLDomain domain = GenerateDomain();
    PDDLProblem problem = GenerateProblem(std::vector<std::string>{ "o1", "o2" }, std::vector<PDDLPredicate>{
        PDDLPredicate("IsTrue", std::vector<PDDLArg>{ PDDLArg("o1", nullptr) })
    });

    PDDLInstance instance = PDDLInstance(&domain, &problem);
    ActionGenerator AG = ActionGenerator(instance.domain);
    std::vector<PDDLActionInstance> actions = AG.GenerateActions(&(instance.problem->initState));
    REQUIRE(1 == actions.size());
}

TEST_CASE(TAG + "Equal") {
    PDDLDomain domain = GenerateDomain(std::vector<PDDLAction>{
            PDDLAction("Action", 
            std::vector<PDDLArg>{
                PDDLArg("arg1"),
                PDDLArg("arg2")
            },
            std::vector<PDDLLiteral>{
                PDDLLiteral(PDDLPredicate("=", std::vector<PDDLArg>{ PDDLArg("arg1"), PDDLArg("arg2") }), true)
            },
            std::vector<PDDLLiteral>())
    });
    PDDLProblem problem = GenerateProblem(std::vector<std::string>{ "o1", "o2", "o3" });

    PDDLInstance instance = PDDLInstance(&domain, &problem);
    ActionGenerator AG = ActionGenerator(instance.domain);
    std::vector<PDDLActionInstance> actions = AG.GenerateActions(&(instance.problem->initState));
    REQUIRE(3 == actions.size());
}

TEST_CASE(TAG + "NotEqual") {
    PDDLDomain domain = GenerateDomain(std::vector<PDDLAction>{
            PDDLAction("Action", 
            std::vector<PDDLArg>{
                PDDLArg("arg1"),
                PDDLArg("arg2")
            },
            std::vector<PDDLLiteral>{
                PDDLLiteral(PDDLPredicate("=", std::vector<PDDLArg>{ PDDLArg("arg1"), PDDLArg("arg2") }), false)
            },
            std::vector<PDDLLiteral>())
    });
    PDDLProblem problem = GenerateProblem(std::vector<std::string>{ "o1", "o2", "o3" });

    PDDLInstance instance = PDDLInstance(&domain, &problem);
    ActionGenerator AG = ActionGenerator(instance.domain);
    std::vector<PDDLActionInstance> actions = AG.GenerateActions(&(instance.problem->initState));
    REQUIRE(6 == actions.size());
}

TEST_CASE(TAG + "Multi") {
    PDDLDomain domain = GenerateDomain(std::vector<PDDLAction>{
            PDDLAction("Action", 
            std::vector<PDDLArg>{
                PDDLArg("arg1"),
                PDDLArg("arg2")
            },
            std::vector<PDDLLiteral>{
                PDDLLiteral(PDDLPredicate("IsTrue2", std::vector<PDDLArg>{ PDDLArg("arg1"), PDDLArg("arg2") }), true)
            },
            std::vector<PDDLLiteral>())
    });
    PDDLProblem problem = GenerateProblem(std::vector<std::string>{ "o1", "o2", "o3", "o4", "o5" }, std::vector<PDDLPredicate>{
        PDDLPredicate("IsTrue2", std::vector<PDDLArg>{ PDDLArg("o1"), PDDLArg("o2") })
    });

    PDDLInstance instance = PDDLInstance(&domain, &problem);
    ActionGenerator AG = ActionGenerator(instance.domain);
    std::vector<PDDLActionInstance> actions = AG.GenerateActions(&(instance.problem->initState));
    REQUIRE(1 == actions.size());
}

TEST_CASE(TAG + "MultiAndUnary") {
    PDDLDomain domain = GenerateDomain(std::vector<PDDLAction>{
            PDDLAction("Action", 
            std::vector<PDDLArg>{
                PDDLArg("arg1"),
                PDDLArg("arg2")
            },
            std::vector<PDDLLiteral>{
                PDDLLiteral(PDDLPredicate("IsTrue", std::vector<PDDLArg>{ PDDLArg("arg1") }), true),
                PDDLLiteral(PDDLPredicate("IsTrue2", std::vector<PDDLArg>{ PDDLArg("arg1"), PDDLArg("arg2") }), true)
            },
            std::vector<PDDLLiteral>())
    });
    PDDLProblem problem = GenerateProblem(std::vector<std::string>{ "o1", "o2", "o3", "o4", "o5" }, std::vector<PDDLPredicate>{
        PDDLPredicate("IsTrue", std::vector<PDDLArg>{ PDDLArg("o1") }),
        PDDLPredicate("IsTrue2", std::vector<PDDLArg>{ PDDLArg("o1"), PDDLArg("o2") })
    });

    PDDLInstance instance = PDDLInstance(&domain, &problem);
    ActionGenerator AG = ActionGenerator(instance.domain);
    std::vector<PDDLActionInstance> actions = AG.GenerateActions(&(instance.problem->initState));
    REQUIRE(1 == actions.size());
}

#pragma endregion Precondition
 */