#include <catch2/catch_test_macros.hpp>

#include <vector>

#include "../../src/JointPaths/Evaluator/Evaluator.hh"

using namespace std;
using namespace JointPaths;

const std::string TAG = "JointPathsEvaluator ";

#pragma region Candidate Removal

TEST_CASE(TAG + "Can_Remove_Candidates_If_Too_Many_1") {
	Evaluator::RunData data;
	data.MaxCandidates = 0;
	Evaluator evaluator(data);
	evaluator.LengthModifier = EvaluationModifiers::LengthModifiers::None;
	evaluator.OccuranceModifier = EvaluationModifiers::OccuranceModifiers::None;

	unordered_map<size_t, JointPath> candidates{
		{1, JointPath(vector<PDDL::ActionInstance*>(), 1)},
		{2, JointPath(vector<PDDL::ActionInstance*>(), 2)},
		{3, JointPath(vector<PDDL::ActionInstance*>(), 3)}
	};

	auto result = evaluator.EvaluateAndSanitizeCandidates(candidates);

	REQUIRE(result.size() == data.MaxCandidates);
}

TEST_CASE(TAG + "Can_Remove_Candidates_If_Too_Many_2") {
	Evaluator::RunData data;
	data.MaxCandidates = 3;
	Evaluator evaluator(data);
	evaluator.LengthModifier = EvaluationModifiers::LengthModifiers::None;
	evaluator.OccuranceModifier = EvaluationModifiers::OccuranceModifiers::None;

	unordered_map<size_t, JointPath> candidates{
		{1, JointPath(vector<PDDL::ActionInstance*>(), 1)},
		{2, JointPath(vector<PDDL::ActionInstance*>(), 2)},
		{3, JointPath(vector<PDDL::ActionInstance*>(), 3)}
	};

	auto result = evaluator.EvaluateAndSanitizeCandidates(candidates);

	REQUIRE(result.size() == data.MaxCandidates);
}

TEST_CASE(TAG + "Wont_Remove_If_Too_Little") {
	Evaluator::RunData data;
	data.MaxCandidates = 10000;
	Evaluator evaluator(data);
	evaluator.LengthModifier = EvaluationModifiers::LengthModifiers::None;
	evaluator.OccuranceModifier = EvaluationModifiers::OccuranceModifiers::None;

	unordered_map<size_t, JointPath> candidates{
		{1, JointPath(vector<PDDL::ActionInstance*>(), 1)},
		{2, JointPath(vector<PDDL::ActionInstance*>(), 2)},
		{3, JointPath(vector<PDDL::ActionInstance*>(), 3)}
	};

	auto result = evaluator.EvaluateAndSanitizeCandidates(candidates);

	REQUIRE(result.size() <= data.MaxCandidates);
}

TEST_CASE(TAG + "Can_Remove_Too_Low_Quality_1") {
	Evaluator::RunData data;
	data.MaxCandidates = 10000;
	data.MinimumQualityPercent = 0.5;
	Evaluator evaluator(data);
	evaluator.LengthModifier = EvaluationModifiers::LengthModifiers::None;
	evaluator.OccuranceModifier = EvaluationModifiers::OccuranceModifiers::None;

	unordered_map<size_t, JointPath> candidates{
		{1, JointPath(vector<PDDL::ActionInstance*>(), 1, 2, 0, 0.1)},
		{2, JointPath(vector<PDDL::ActionInstance*>(), 2, 2, 0, 0.5)},
		{3, JointPath(vector<PDDL::ActionInstance*>(), 3, 2, 0, 1)}
	};

	auto result = evaluator.EvaluateAndSanitizeCandidates(candidates);

	REQUIRE(result.size() == 2);
}

TEST_CASE(TAG + "Can_Remove_Too_Low_Quality_2") {
	Evaluator::RunData data;
	data.MaxCandidates = 10000;
	data.MinimumQualityPercent = 0.6;
	Evaluator evaluator(data);
	evaluator.LengthModifier = EvaluationModifiers::LengthModifiers::None;
	evaluator.OccuranceModifier = EvaluationModifiers::OccuranceModifiers::None;

	unordered_map<size_t, JointPath> candidates{
		{1, JointPath(vector<PDDL::ActionInstance*>(), 1, 2, 0, 0.1)},
		{2, JointPath(vector<PDDL::ActionInstance*>(), 2, 2, 0, 0.5)},
		{3, JointPath(vector<PDDL::ActionInstance*>(), 3, 2, 0, 1)}
	};

	auto result = evaluator.EvaluateAndSanitizeCandidates(candidates);

	REQUIRE(result.size() == 1);
}

TEST_CASE(TAG + "Can_Remove_Too_Low_Quality_3") {
	Evaluator::RunData data;
	data.MaxCandidates = 10000;
	data.MinimumQualityPercent = 0.4;
	Evaluator evaluator(data);
	evaluator.LengthModifier = EvaluationModifiers::LengthModifiers::None;
	evaluator.OccuranceModifier = EvaluationModifiers::OccuranceModifiers::None;

	unordered_map<size_t, JointPath> candidates{
		{1, JointPath(vector<PDDL::ActionInstance*>(), 1, 2, 0, 0.1)},
		{2, JointPath(vector<PDDL::ActionInstance*>(), 2, 2, 0, 0.5)},
		{3, JointPath(vector<PDDL::ActionInstance*>(), 3, 2, 0, 1)}
	};

	auto result = evaluator.EvaluateAndSanitizeCandidates(candidates);

	REQUIRE(result.size() == 2);
}

#pragma endregion

#pragma region Default Modifiers

TEST_CASE(TAG + "Sets_Default_Modifiers_If_None_Given") {
	Evaluator::RunData data;
	Evaluator evaluator(data);

	REQUIRE(evaluator.LengthModifier == nullptr);
	REQUIRE(evaluator.OccuranceModifier == nullptr);

	auto result = evaluator.EvaluateAndSanitizeCandidates(unordered_map<size_t, JointPath>());

	REQUIRE(evaluator.LengthModifier != nullptr);
	REQUIRE(evaluator.OccuranceModifier != nullptr);
}

#pragma endregion

#pragma region Sorting

TEST_CASE(TAG + "Can_Sort_Candidates") {
	Evaluator::RunData data;
	data.MaxCandidates = 10000;
	Evaluator evaluator(data);
	evaluator.LengthModifier = EvaluationModifiers::LengthModifiers::None;
	evaluator.OccuranceModifier = EvaluationModifiers::OccuranceModifiers::None;

	unordered_map<size_t, JointPath> candidates{
		{1, JointPath(vector<PDDL::ActionInstance*>(), 1, 2, 0, 1)},
		{2, JointPath(vector<PDDL::ActionInstance*>(), 2, 2, 0, 0.2)},
		{3, JointPath(vector<PDDL::ActionInstance*>(), 3, 2, 0, 0.4)}
	};

	auto result = evaluator.EvaluateAndSanitizeCandidates(candidates);

	REQUIRE(result.size() == candidates.size());
	for (int i = 1; i < result.size(); i++) {
		REQUIRE(result.at(i - 1).Quality > result.at(i).Quality);
	}
}

#pragma endregion

#pragma region Length Modifiers

TEST_CASE(TAG + "Can_Set_Lenght_Modifier_None") {
	Evaluator::RunData data;
	data.MaxCandidates = 10000;
	Evaluator evaluator(data);
	evaluator.LengthModifier = EvaluationModifiers::LengthModifiers::None;
	evaluator.OccuranceModifier = EvaluationModifiers::OccuranceModifiers::None;

	// Remember, that the results is sorted!
	vector<int> expectedQuality{
		100,
		100,
		100,
	};

	unordered_map<size_t, JointPath> candidates{
		{1, JointPath(vector<PDDL::ActionInstance*>(), 1, 2, 2, 1)},
		{2, JointPath(vector<PDDL::ActionInstance*>(), 2, 2, 4, 1)},
		{3, JointPath(vector<PDDL::ActionInstance*>(), 3, 2, 6, 1)}
	};

	auto result = evaluator.EvaluateAndSanitizeCandidates(candidates);

	REQUIRE(result.size() == candidates.size());
	for (int i = 0; i < result.size(); i++) {
		REQUIRE((int)(result.at(i).Quality * 100) == expectedQuality.at(i));
	}
}

TEST_CASE(TAG + "Can_Set_Lenght_Modifier_Default") {
	Evaluator::RunData data;
	data.MaxCandidates = 10000;
	Evaluator evaluator(data);
	evaluator.LengthModifier = EvaluationModifiers::LengthModifiers::Default;
	evaluator.OccuranceModifier = EvaluationModifiers::OccuranceModifiers::None;

	// Remember, that the results is sorted!
	vector<int> expectedQuality{
		100,
		66,
		33,
	};

	unordered_map<size_t, JointPath> candidates{
		{1, JointPath(vector<PDDL::ActionInstance*>(), 1, 2, 2, 1)},
		{2, JointPath(vector<PDDL::ActionInstance*>(), 2, 2, 4, 1)},
		{3, JointPath(vector<PDDL::ActionInstance*>(), 3, 2, 6, 1)}
	};

	auto result = evaluator.EvaluateAndSanitizeCandidates(candidates);

	REQUIRE(result.size() == candidates.size());
	for (int i = 0; i < result.size(); i++) {
		REQUIRE((int)(result.at(i).Quality * 100) == expectedQuality.at(i));
	}
}

TEST_CASE(TAG + "Can_Set_Lenght_Modifier_LengthBias") {
	Evaluator::RunData data;
	data.MaxCandidates = 10000;
	Evaluator evaluator(data);
	evaluator.LengthModifier = EvaluationModifiers::LengthModifiers::LengthBias;
	evaluator.OccuranceModifier = EvaluationModifiers::OccuranceModifiers::None;

	// Remember, that the results is sorted!
	vector<int> expectedQuality{
		100,
		50,
		25,
	};

	unordered_map<size_t, JointPath> candidates{
		{1, JointPath(vector<PDDL::ActionInstance*>(), 1, 2, 2, 1)},
		{2, JointPath(vector<PDDL::ActionInstance*>(), 2, 2, 4, 1)},
		{3, JointPath(vector<PDDL::ActionInstance*>(), 3, 2, 6, 1)}
	};

	auto result = evaluator.EvaluateAndSanitizeCandidates(candidates);

	REQUIRE(result.size() == candidates.size());
	for (int i = 0; i < result.size(); i++) {
		REQUIRE((int)(result.at(i).Quality * 100) == expectedQuality.at(i));
	}
}

#pragma endregion

#pragma region Occurance Modifiers

TEST_CASE(TAG + "Can_Set_Occurance_Modifier_None") {
	Evaluator::RunData data;
	data.MaxCandidates = 10000;
	Evaluator evaluator(data);
	evaluator.LengthModifier = EvaluationModifiers::LengthModifiers::None;
	evaluator.OccuranceModifier = EvaluationModifiers::OccuranceModifiers::None;

	// Remember, that the results is sorted!
	vector<int> expectedQuality{
		100,
		100,
		100,
	};

	unordered_map<size_t, JointPath> candidates{
		{1, JointPath(vector<PDDL::ActionInstance*>(), 1, 2, 2, 1)},
		{2, JointPath(vector<PDDL::ActionInstance*>(), 2, 2, 4, 1)},
		{3, JointPath(vector<PDDL::ActionInstance*>(), 3, 2, 6, 1)}
	};

	auto result = evaluator.EvaluateAndSanitizeCandidates(candidates);

	REQUIRE(result.size() == candidates.size());
	for (int i = 0; i < result.size(); i++) {
		REQUIRE((int)(result.at(i).Quality * 100) == expectedQuality.at(i));
	}
}

TEST_CASE(TAG + "Can_Set_Occurance_Modifier_Default") {
	Evaluator::RunData data;
	data.MaxCandidates = 10000;
	Evaluator evaluator(data);
	evaluator.LengthModifier = EvaluationModifiers::LengthModifiers::None;
	evaluator.OccuranceModifier = EvaluationModifiers::OccuranceModifiers::Default;

	// Remember, that the results is sorted!
	vector<int> expectedQuality{
		100,
		66,
		33,
	};

	unordered_map<size_t, JointPath> candidates{
		{1, JointPath(vector<PDDL::ActionInstance*>(), 1, 2, 2, 1)},
		{2, JointPath(vector<PDDL::ActionInstance*>(), 2, 4, 4, 1)},
		{3, JointPath(vector<PDDL::ActionInstance*>(), 3, 6, 6, 1)}
	};

	auto result = evaluator.EvaluateAndSanitizeCandidates(candidates);

	REQUIRE(result.size() == candidates.size());
	for (int i = 0; i < result.size(); i++) {
		REQUIRE((int)(result.at(i).Quality * 100) == expectedQuality.at(i));
	}
}

TEST_CASE(TAG + "Can_Set_Occurance_Modifier_LowOccuranceBias") {
	Evaluator::RunData data;
	data.MaxCandidates = 10000;
	Evaluator evaluator(data);
	evaluator.LengthModifier = EvaluationModifiers::LengthModifiers::None;
	evaluator.OccuranceModifier = EvaluationModifiers::OccuranceModifiers::LowOccuranceBias;

	// Remember, that the results is sorted!
	vector<int> expectedQuality{
		50,
		25,
		16,
	};

	unordered_map<size_t, JointPath> candidates{
		{1, JointPath(vector<PDDL::ActionInstance*>(), 1, 2, 2, 1)},
		{2, JointPath(vector<PDDL::ActionInstance*>(), 2, 4, 4, 1)},
		{3, JointPath(vector<PDDL::ActionInstance*>(), 3, 6, 6, 1)}
	};

	auto result = evaluator.EvaluateAndSanitizeCandidates(candidates);

	REQUIRE(result.size() == candidates.size());
	for (int i = 0; i < result.size(); i++) {
		REQUIRE((int)(result.at(i).Quality * 100) == expectedQuality.at(i));
	}
}

#pragma endregion

