#include <catch2/catch_test_macros.hpp>
#include <string>
#include <unordered_set>

using namespace std;

#include "../../src/MacroGenerator/InstanceGenerator.hh"

const std::string TAG = "Macro ";

TEST_CASE(TAG + "Can_Make_Unary_Literals_1") {
    InstanceGenerator generator;

    PDDLDomain domain;
    PDDLProblem problem({ "obj1","obj2","obj3","obj4" });
    PDDLInstance instance(&domain, &problem);
    vector<Macro> macros{
    };

    auto result = generator.GenerateInstance(&domain, &problem, &macros);

    REQUIRE(result.domain->predicates.size() == instance.domain->predicates.size());
}

TEST_CASE(TAG + "Can_Make_Unary_Literals_2") {
    InstanceGenerator generator;

    PDDLDomain domain;
    PDDLProblem problem({"obj1","obj2","obj3","obj4"});
    PDDLInstance instance(&domain, &problem);
    vector<Macro> macros{
        Macro(
            GroundedAction(
                "action", 
                {1,2}, 
                {
                    {
                        GroundedLiteral(1, {1,2}), 
                        true
                    }
                }, 
                {
                    {
                        GroundedLiteral(1, {1,2}), 
                        false
                    }
                }), 
            vector<PDDLActionInstance>())
    };

    auto result = generator.GenerateInstance(&domain, &problem, &macros);

    REQUIRE(result.domain->predicates.size() == instance.domain->predicates.size() + 2);
}

TEST_CASE(TAG + "Can_Make_Macro_Action_1") {
    InstanceGenerator generator;

    PDDLDomain domain;
    PDDLProblem problem({ "obj1","obj2","obj3","obj4" });
    PDDLInstance instance(&domain, &problem);
    vector<Macro> macros{
        Macro(
            GroundedAction(
                "action",
                {1,2},
                {
                    {
                        GroundedLiteral(1, {1,2}),
                        true
                    }
                },
                {
                    {
                        GroundedLiteral(1, {1,2}),
                        false
                    }
                }),
            vector<PDDLActionInstance>())
    };

    auto result = generator.GenerateInstance(&domain, &problem, &macros);

    REQUIRE(result.domain->actions.size() == instance.domain->actions.size() + 1);
}

TEST_CASE(TAG + "Can_Make_Macro_Action_2") {
    InstanceGenerator generator;

    PDDLDomain domain;
    PDDLProblem problem({ "obj1","obj2","obj3","obj4" });
    PDDLInstance instance(&domain, &problem);
    vector<Macro> macros{
        Macro(
            GroundedAction(
                "action",
                {1,2},
                {
                    {
                        GroundedLiteral(1, {1,2}),
                        true
                    }
                },
                {
                    {
                        GroundedLiteral(1, {1,2}),
                        false
                    }
                }),
            vector<PDDLActionInstance>()),
        Macro(
            GroundedAction(
                "action2",
                {1,2},
                {
                    {
                        GroundedLiteral(1, {1,2}),
                        true
                    }
                },
                {
                    {
                        GroundedLiteral(1, {1,2}),
                        false
                    }
                }),
            vector<PDDLActionInstance>())
    };

    auto result = generator.GenerateInstance(&domain, &problem, &macros);

    REQUIRE(result.domain->actions.size() == instance.domain->actions.size() + 2);
}

TEST_CASE(TAG + "Can_Set_Init_State_1") {
    InstanceGenerator generator;

    PDDLDomain domain;
    PDDLProblem problem({ "obj1","obj2","obj3","obj4" });
    PDDLInstance instance(&domain, &problem);
    vector<Macro> macros{
    };

    auto result = generator.GenerateInstance(&domain, &problem, &macros);

    REQUIRE(result.problem->initState.unaryFacts == instance.problem->initState.unaryFacts);
}

TEST_CASE(TAG + "Can_Set_Init_State_2") {
    InstanceGenerator generator;

    PDDLDomain domain;
    PDDLProblem problem({ "obj1","obj2","obj3","obj4" });
    PDDLInstance instance(&domain, &problem);
    vector<Macro> macros{
        Macro(
            GroundedAction(
                "action",
                {1,2},
                {
                    {
                        GroundedLiteral(1, {1,2}),
                        true
                    }
                },
                {
                    {
                        GroundedLiteral(1, {1,2}),
                        false
                    }
                }),
            vector<PDDLActionInstance>())
    };

    auto result = generator.GenerateInstance(&domain, &problem, &macros);

    REQUIRE(result.problem->initState.unaryFacts.size() == instance.problem->initState.unaryFacts.size() + 2);
}
