#include <catch2/catch_test_macros.hpp>

#include "../../src/IntermediatePDDL/PDDLArg.hh"
#include "../../src/IntermediatePDDL/PDDLInstance.hh"
#include "../../src/Walker/ActionGenerator.hpp"

const std::string TAG = "ActionGenerator ";

TEST_CASE(TAG + "Empty") {
    PDDLInstance instance = PDDLInstance(new PDDLDomain(), new PDDLProblem());
    ActionGenerator AG = ActionGenerator(instance.domain);
    std::vector<PDDLActionInstance> actions = AG.GenerateActions(&instance.problem->initState);
    REQUIRE(actions.size() == 0);
    free(instance.domain);
    free(instance.problem);
}

TEST_CASE(TAG + "1 legal") {
    PDDLDomain domain = PDDLDomain();
    domain.predicates = std::vector<PDDLPredicate>{
        PDDLPredicate("IsTrue", std::vector<PDDLArg>{
            PDDLArg("SomeObject", nullptr)
        })
    };
    domain.actions = std::vector<PDDLAction>{
        PDDLAction("Action", 
        std::vector<PDDLArg>{
            PDDLArg("arg1", nullptr)
        },
        std::vector<PDDLLiteral>{
            PDDLLiteral(PDDLPredicate("IsTrue", std::vector<PDDLArg>{ PDDLArg("arg1", nullptr) }), false)
        },
        std::vector<PDDLLiteral>{
            PDDLLiteral(PDDLPredicate("IsTrue", std::vector<PDDLArg>{ PDDLArg("arg1", nullptr) }), true)
        })
    };
    PDDLProblem problem = PDDLProblem();
    problem.objects = std::vector<std::string>{ "o1" };
    problem.initState = PDDLState();
    problem.initState.objects = &problem.objects;

    PDDLInstance instance = PDDLInstance(&domain, &problem);
    ActionGenerator AG = ActionGenerator(instance.domain);
    std::vector<PDDLActionInstance> actions = AG.GenerateActions(&(instance.problem->initState));
    REQUIRE(actions.size() == 1);
}

/*

PDDLInstance GenerateInstance() {
    PDDLDomain* domain = new PDDLDomain();
    domain->name = "test domain";
    //domain.typeDict = std::unordered_map<std::string, PDDLType*>{
    //    ("type1", nullptr),
    //    ("type2", nullptr)
    //};
    domain->predicates = std::vector<PDDLPredicate>{
        PDDLPredicate("predicate1", std::vector<PDDLArg>{
            PDDLArg(0, "arg1", nullptr),
            PDDLArg(1, "arg2", nullptr)
        })
    };
    domain->requirements = std::vector<std::string>{
        "r1",
        "r2"
    };
    domain->actions = std::vector<PDDLAction>{
        PDDLAction("action1", 
        std::vector<PDDLArg>{
            PDDLArg(0, "arg1", nullptr),
            PDDLArg(1, "arg2", nullptr)
        },
        std::vector<PDDLLiteral>{
            PDDLLiteral(PDDLPredicate("p1", 
            std::vector<PDDLArg>{PDDLArg(0, "?x", nullptr)}), true)
        },
        std::vector<PDDLLiteral>{
            PDDLLiteral(PDDLPredicate("p1", 
            std::vector<PDDLArg>{PDDLArg(0, "?x", nullptr)}), false)
        })
    };
    return PDDLInstance(domain, nullptr);
}

TEST_CASE(TAG + "Walk") {
    PDDLInstance instance = GenerateInstance();
    ActionGenerator AG = ActionGenerator(instance.domain);
    //auto actions = AG.GenerateActions()
    free(instance.domain);
    free(instance.problem);
}
*/