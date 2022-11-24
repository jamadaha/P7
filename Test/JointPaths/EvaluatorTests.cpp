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

	unordered_map<size_t, JointPath> candidates{
		{1, JointPath(vector<PDDLActionInstance*>(), 1)},
		{2, JointPath(vector<PDDLActionInstance*>(), 2)},
		{3, JointPath(vector<PDDLActionInstance*>(), 3)}
	};

	auto result = evaluator.EvaluateAndSanitizeCandidates(candidates);

	REQUIRE(result.size() == data.MaxCandidates);
}

TEST_CASE(TAG + "Can_Remove_Candidates_If_Too_Many_2") {
	Evaluator::RunData data;
	data.MaxCandidates = 3;
	Evaluator evaluator(data);

	unordered_map<size_t, JointPath> candidates{
		{1, JointPath(vector<PDDLActionInstance*>(), 1)},
		{2, JointPath(vector<PDDLActionInstance*>(), 2)},
		{3, JointPath(vector<PDDLActionInstance*>(), 3)}
	};

	auto result = evaluator.EvaluateAndSanitizeCandidates(candidates);

	REQUIRE(result.size() == data.MaxCandidates);
}

TEST_CASE(TAG + "Wont_Remove_If_Too_Little") {
	Evaluator::RunData data;
	data.MaxCandidates = 10000;
	Evaluator evaluator(data);

	unordered_map<size_t, JointPath> candidates{
		{1, JointPath(vector<PDDLActionInstance*>(), 1)},
		{2, JointPath(vector<PDDLActionInstance*>(), 2)},
		{3, JointPath(vector<PDDLActionInstance*>(), 3)}
	};

	auto result = evaluator.EvaluateAndSanitizeCandidates(candidates);

	REQUIRE(result.size() <= data.MaxCandidates);
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
