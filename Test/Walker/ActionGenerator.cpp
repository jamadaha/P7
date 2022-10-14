#include <catch2/catch_test_macros.hpp>

#include "../../src/IntermediatePDDL/PDDLArg.hh"
#include "../../src/IntermediatePDDL/PDDLInstance.hh"
#include "../../src/Walker/ActionGenerator.hpp"

const std::string TAG = "ActionGenerator ";

PDDLDomain GenerateDomain(std::vector<PDDLAction> actions = std::vector<PDDLAction>()) {
    PDDLDomain domain = PDDLDomain();
    domain.predicates = std::vector<PDDLPredicate>{
        PDDLPredicate("IsTrue", std::vector<PDDLArg>{
            PDDLArg("SomeObject", nullptr)
        }),
        PDDLPredicate("IsTrue2", std::vector<PDDLArg>{
            PDDLArg("SomeObject", nullptr),
            PDDLArg("SomeOtherObject", nullptr)
        })
    };
    if (actions.size() == 0)
        domain.actions = std::vector<PDDLAction>{
            PDDLAction("Action", 
            std::vector<PDDLArg>{
                PDDLArg("arg1", nullptr)
            },
            std::vector<PDDLLiteral>{
                PDDLLiteral(PDDLPredicate("IsTrue", std::vector<PDDLArg>{ PDDLArg("arg1", nullptr) }), false)
            },
            std::vector<PDDLLiteral>())
        };
    else
        domain.actions = actions;
    return domain;
}

PDDLProblem GenerateProblem(std::vector<std::string> objects = std::vector<std::string>(), std::vector<PDDLPredicate> state = std::vector<PDDLPredicate>()) {
    PDDLProblem problem = PDDLProblem();
    problem.objects = objects;
    problem.initState = PDDLState();
    problem.initState.objects = &problem.objects;
    problem.initState.state = state;
    return problem;
}

#pragma region Precondition

TEST_CASE(TAG + "Empty") {
    PDDLInstance instance = PDDLInstance(new PDDLDomain(), new PDDLProblem());
    ActionGenerator AG = ActionGenerator(instance.domain);
    std::vector<PDDLActionInstance> actions = AG.GenerateActions(&instance.problem->initState);
    REQUIRE(actions.size() == 0);
    free(instance.domain);
    free(instance.problem);
}

TEST_CASE(TAG + "Unary - 0 legal") {
    PDDLDomain domain = GenerateDomain();
    PDDLProblem problem = GenerateProblem(std::vector<std::string>{  });

    PDDLInstance instance = PDDLInstance(&domain, &problem);
    ActionGenerator AG = ActionGenerator(instance.domain);
    std::vector<PDDLActionInstance> actions = AG.GenerateActions(&(instance.problem->initState));
    REQUIRE(0 == actions.size());
}

TEST_CASE(TAG + "Unary - 1 legal") {
    PDDLDomain domain = GenerateDomain();
    PDDLProblem problem = GenerateProblem(std::vector<std::string>{ "o1" });

    PDDLInstance instance = PDDLInstance(&domain, &problem);
    ActionGenerator AG = ActionGenerator(instance.domain);
    std::vector<PDDLActionInstance> actions = AG.GenerateActions(&(instance.problem->initState));
    REQUIRE(1 == actions.size());
}

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

#pragma endregion Precondition
