#include <catch2/catch_test_macros.hpp>
#include <string>
#include <unordered_set>

using namespace std;

#include "../../src/Macros/Instantiators/Instantiator.hh"

const std::string TAG = "Macros::Macro ";

TEST_CASE(TAG + "Can_Make_Unary_Literals_1") {
    Macros::Instantiator generator;

    PDDLDomain domain;
    PDDLProblem problem({ "obj1","obj2","obj3","obj4" });
    PDDLInstance instance(&domain, &problem);
    vector<Macros::Macro> macros{
    };

    auto result = generator.GenerateInstance(&domain, &problem, &macros);

    REQUIRE(result.domain->predicates.size() == instance.domain->predicates.size());
}

TEST_CASE(TAG + "Can_Make_Unary_Literals_2") {
    Macros::Instantiator generator;

    PDDLDomain domain;
    PDDLProblem problem({"obj1","obj2","obj3","obj4"});
    PDDLInstance instance(&domain, &problem);
    vector<Macros::Macro> macros{
        Macros::Macro(
            Macros::GroundedAction(
                "action", 
                {1,2}, 
                {
                    {
                        Macros::GroundedLiteral(1, {1,2}), 
                        true
                    }
                }, 
                {
                    {
                        Macros::GroundedLiteral(1, {1,2}), 
                        false
                    }
                }), 
            vector<PDDLActionInstance>())
    };

    auto result = generator.GenerateInstance(&domain, &problem, &macros);

    REQUIRE(result.domain->predicates.size() == instance.domain->predicates.size() + 2);
}

TEST_CASE(TAG + "Can_Make_Macro_Action_1") {
    Macros::Instantiator generator;

    PDDLDomain domain;
    PDDLProblem problem({ "obj1","obj2","obj3","obj4" });
    PDDLInstance instance(&domain, &problem);
    vector<Macros::Macro> macros{
        Macros::Macro(
            Macros::GroundedAction(
                "action",
                {1,2},
                {
                    {
                        Macros::GroundedLiteral(1, {1,2}),
                        true
                    }
                },
                {
                    {
                        Macros::GroundedLiteral(1, {1,2}),
                        false
                    }
                }),
            vector<PDDLActionInstance>())
    };

    auto result = generator.GenerateInstance(&domain, &problem, &macros);

    REQUIRE(result.domain->actions.size() == instance.domain->actions.size() + 1);
}

TEST_CASE(TAG + "Can_Make_Macro_Action_2") {
    Macros::Instantiator generator;

    PDDLDomain domain;
    PDDLProblem problem({ "obj1","obj2","obj3","obj4" });
    PDDLInstance instance(&domain, &problem);
    vector<Macros::Macro> macros{
        Macros::Macro(
            Macros::GroundedAction(
                "action",
                {1,2},
                {
                    {
                        Macros::GroundedLiteral(1, {1,2}),
                        true
                    }
                },
                {
                    {
                        Macros::GroundedLiteral(1, {1,2}),
                        false
                    }
                }),
            vector<PDDLActionInstance>()),
        Macros::Macro(
            Macros::GroundedAction(
                "action2",
                {1,2},
                {
                    {
                        Macros::GroundedLiteral(1, {1,2}),
                        true
                    }
                },
                {
                    {
                        Macros::GroundedLiteral(1, {1,2}),
                        false
                    }
                }),
            vector<PDDLActionInstance>())
    };

    auto result = generator.GenerateInstance(&domain, &problem, &macros);

    REQUIRE(result.domain->actions.size() == instance.domain->actions.size() + 2);
}

TEST_CASE(TAG + "Can_Set_Init_State_1") {
    Macros::Instantiator generator;

    PDDLDomain domain;
    PDDLProblem problem({ "obj1","obj2","obj3","obj4" });
    PDDLInstance instance(&domain, &problem);
    vector<Macros::Macro> macros{
    };

    auto result = generator.GenerateInstance(&domain, &problem, &macros);

    REQUIRE(result.problem->initState.unaryFacts == instance.problem->initState.unaryFacts);
}

TEST_CASE(TAG + "Can_Set_Init_State_2") {
    Macros::Instantiator generator;

    PDDLDomain domain;
    PDDLProblem problem({ "obj1","obj2","obj3","obj4" });
    PDDLInstance instance(&domain, &problem);
    vector<Macros::Macro> macros{
        Macros::Macro(
            Macros::GroundedAction(
                "action",
                {1,2},
                {
                    {
                        Macros::GroundedLiteral(1, {1,2}),
                        true
                    }
                },
                {
                    {
                        Macros::GroundedLiteral(1, {1,2}),
                        false
                    }
                }),
            vector<PDDLActionInstance>())
    };

    auto result = generator.GenerateInstance(&domain, &problem, &macros);

    REQUIRE(result.problem->initState.unaryFacts.size() == instance.problem->initState.unaryFacts.size() + 2);
}
