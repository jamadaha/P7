#include <catch2/catch_test_macros.hpp>
#include <string>

#include "../../src/SAS/Rebuilder/Rebuilder.hh"

using namespace std;
using namespace SAS;

const std::string TAG = "Rebuilder ";

void CheckPlans(Plan sourcePlan, Plan checkPlan) {
	REQUIRE(sourcePlan.cost == checkPlan.cost);
	REQUIRE(sourcePlan.macrosUsed == checkPlan.macrosUsed);
	for (int i = 0; i < sourcePlan.actions.size(); i++) {
		REQUIRE(sourcePlan.actions.at(i).name == checkPlan.actions.at(i).name);
		for (int j = 0; j < sourcePlan.actions.at(i).parameters.size(); j++)
			REQUIRE(sourcePlan.actions.at(i).parameters.at(j) == checkPlan.actions.at(i).parameters.at(j));
	}
}

TEST_CASE(TAG + "CanRebuild-NoMacros") {
	PDDL::Domain domain;
	PDDL::Problem problem;
	PDDL::Instance instance(&domain, &problem);

	vector<Macros::Macro> macros;
	vector<SAS::Action> actions{
		SAS::Action("action1", {"a","b"}),
		SAS::Action("action2", {"a","b"})
	};
	Plan sourcePlan = Plan(actions,2,0);

	SAS::Rebuilder rebuilder = Rebuilder(&instance, &macros);
	Plan checkPlan = rebuilder.RebuildSASPlan(&sourcePlan);

	CheckPlans(sourcePlan, checkPlan);
}

TEST_CASE(TAG + "CanRebuild-OneMacro") {
	auto action1 = PDDL::Action("action1");
	auto action2 = PDDL::Action("action2");
	auto action3 = PDDL::Action("action3");
	PDDL::Domain domain("a", {}, {}, {}, {action1, action2, action3});
	PDDL::Problem problem("a", &domain, { "obj1", "obj2" }, {}, PDDL::State(), PDDL::State());
	PDDL::Instance instance(&domain, &problem);

	vector<Macros::Macro> macros{
		Macros::Macro(Macros::GroundedAction("action"), {
				PDDLActionInstance(&action1, {0,1}),
				PDDLActionInstance(&action2, {1,0})
			})
	};
	vector<SAS::Action> actions{
		SAS::Action("macro-action", {"obj1","obj2"})
	};
	Plan sourcePlan = Plan(actions, 2, 0);
	vector<SAS::Action> expActions{
		SAS::Action("action1", {"obj1","obj2"}),
		SAS::Action("action2", {"obj2","obj1"})
	};
	Plan expectedPlan = Plan(expActions, 2, 1);

	SAS::Rebuilder rebuilder = Rebuilder(&instance, &macros);
	Plan checkPlan = rebuilder.RebuildSASPlan(&sourcePlan);

	CheckPlans(expectedPlan, checkPlan);
}

TEST_CASE(TAG + "CanRebuild-MultipleMacro") {
	auto action1 = PDDL::Action("action1");
	auto action2 = PDDL::Action("action2");
	auto action3 = PDDL::Action("action3");
	PDDL::Domain domain("a", {}, {}, {}, { action1, action2, action3 });
	PDDL::Problem problem("a", &domain, { "obj1", "obj2" }, {}, PDDL::State(), PDDL::State());
	PDDL::Instance instance(&domain, &problem);

	vector<Macros::Macro> macros{
		Macros::Macro(Macros::GroundedAction("action1"), {
				PDDLActionInstance(&action1, {0,1}),
				PDDLActionInstance(&action2, {1,0})
			}),
		Macros::Macro(Macros::GroundedAction("action2"), {
				PDDLActionInstance(&action2, {0,1}),
				PDDLActionInstance(&action3, {1,0})
			}),
		Macros::Macro(Macros::GroundedAction("action3"), {
				PDDLActionInstance(&action1, {0,1}),
				PDDLActionInstance(&action3, {1,0})
			})
	};
	vector<SAS::Action> actions{
		SAS::Action("macro-action1", {"obj1","obj2"}),
		SAS::Action("macro-action2", {"obj1","obj2"}),
		SAS::Action("macro-action3", {"obj1","obj2"})
	};
	Plan sourcePlan = Plan(actions, 2, 0);
	vector<SAS::Action> expActions{
		SAS::Action("action1", {"obj1","obj2"}),
		SAS::Action("action2", {"obj2","obj1"}),
		SAS::Action("action2", {"obj1","obj2"}),
		SAS::Action("action3", {"obj2","obj1"}),
		SAS::Action("action1", {"obj1","obj2"}),
		SAS::Action("action3", {"obj2","obj1"})
	};
	Plan expectedPlan = Plan(expActions, 6, 3);

	SAS::Rebuilder rebuilder = Rebuilder(&instance, &macros);
	Plan checkPlan = rebuilder.RebuildSASPlan(&sourcePlan);

	CheckPlans(expectedPlan, checkPlan);
}
