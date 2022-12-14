#include <catch2/catch_test_macros.hpp>

#include <vector>
#include <unordered_set>

#include "../../src/Helpers/AlgorithmHelper.hh"
#include "../../src/Helpers/Hashes.hh"

using namespace std;
const string TAG = "AlgorithmHelper ";

#pragma region InsertAll

TEST_CASE(TAG + "InsertAll-UnorderedSet-None") {
	unordered_set<unsigned int> set1{
	};
	unordered_set<unsigned int> set2{
	};

	AlgorithmHelper::InsertAll(set2, set1);

	REQUIRE(set2 == set1);
	REQUIRE(set1.size() == 0);
	REQUIRE(set2.size() == 0);
}

TEST_CASE(TAG + "InsertAll-UnorderedSet-Some") {
	unordered_set<unsigned int> set1{
		1,2,3
	};
	unordered_set<unsigned int> set2{
	};

	AlgorithmHelper::InsertAll(set2, set1);

	REQUIRE(set2 == set1);
}

TEST_CASE(TAG + "InsertAll-UnorderedSet-Mixed") {
	unordered_set<unsigned int> set1{
		1,2,3
	};
	unordered_set<unsigned int> set2{
		4,5
	};
	unordered_set<unsigned int> expectSet{
		4,5,1,2,3
	};

	AlgorithmHelper::InsertAll(set2, set1);

	REQUIRE(set2 == expectSet);
}

TEST_CASE(TAG + "InsertAll-Vector-None") {
	vector<unsigned int> set1{
	};
	vector<unsigned int> set2{
	};

	AlgorithmHelper::InsertAll(set2, set1);

	REQUIRE(set2 == set1);
	REQUIRE(set1.size() == 0);
	REQUIRE(set2.size() == 0);
}

TEST_CASE(TAG + "InsertAll-Vector-Some") {
	vector<unsigned int> set1{
		1,2,3
	};
	vector<unsigned int> set2{
	};

	AlgorithmHelper::InsertAll(set2, set1);

	REQUIRE(set2 == set1);

}

TEST_CASE(TAG + "InsertAll-Vector-Mixed") {
	vector<unsigned int> set1{
		1,2,3
	};
	vector<unsigned int> set2{
		4,5
	};
	vector<unsigned int> expectSet{
		4,5,1,2,3
	};

	AlgorithmHelper::InsertAll(set2, set1);

	REQUIRE(set2 == expectSet);
}

#pragma endregion

#pragma region Intersect

TEST_CASE(TAG + "Intersect-unordered_set-None") {
	unordered_set<unsigned int> set1{
		1,2,3
	};
	unordered_set<unsigned int> set2{
		5,6,7
	};
	unordered_set<unsigned int> expectSet{
	};

	AlgorithmHelper::Intersect(set2, set1);

	REQUIRE(set2 == expectSet);
}

TEST_CASE(TAG + "Intersect-unordered_set-pair-None") {
	unordered_set<pair<unsigned int, unsigned int>> set1{
		make_pair(1,2),
		make_pair(3,4)
	};
	unordered_set<pair<unsigned int, unsigned int>> set2{
		make_pair(3,6),
		make_pair(7,8)
	};
	unordered_set<pair<unsigned int, unsigned int>> expectSet{
	};

	AlgorithmHelper::Intersect(set2, set1);

	REQUIRE(set2 == expectSet);
}

TEST_CASE(TAG + "Intersect-unordered_set-Single") {
	unordered_set<unsigned int> set1{
		1,2,3
	};
	unordered_set<unsigned int> set2{
		3,4,5
	};
	unordered_set<unsigned int> expectSet{
		3
	};

	AlgorithmHelper::Intersect(set2, set1);

	REQUIRE(set2 == expectSet);
}

TEST_CASE(TAG + "Intersect-unordered_set-pair-Single") {
	unordered_set<pair<unsigned int, unsigned int>> set1{
		make_pair(1,2),
		make_pair(3,4)
	};
	unordered_set<pair<unsigned int, unsigned int>> set2{
		make_pair(3,4),
		make_pair(7,8)
	};
	unordered_set<pair<unsigned int, unsigned int>> expectSet{
		make_pair(3,4)
	};

	AlgorithmHelper::Intersect(set2, set1);

	REQUIRE(set2 == expectSet);
}

TEST_CASE(TAG + "Intersect-unordered_set-Multiple") {
	unordered_set<unsigned int> set1{
		1,2,3
	};
	unordered_set<unsigned int> set2{
		2,3,4
	};
	unordered_set<unsigned int> expectSet{
		2,3
	};

	AlgorithmHelper::Intersect(set2, set1);

	REQUIRE(set2 == expectSet);
}

TEST_CASE(TAG + "Intersect-unordered_set-pair-Multiple") {
	unordered_set<pair<unsigned int, unsigned int>> set1{
		make_pair(1,2),
		make_pair(4,4),
		make_pair(3,4)
	};
	unordered_set<pair<unsigned int, unsigned int>> set2{
		make_pair(4,4),
		make_pair(3,4),
		make_pair(7,8)
	};
	unordered_set<pair<unsigned int, unsigned int>> expectSet{
		make_pair(4,4),
		make_pair(3,4)
	};

	AlgorithmHelper::Intersect(set2, set1);

	REQUIRE(set2 == expectSet);
}

TEST_CASE(TAG + "Intersect-unordered_set-Full") {
	unordered_set<unsigned int> set1{
		1,2,3
	};
	unordered_set<unsigned int> set2{
		1,2,3
	};
	unordered_set<unsigned int> expectSet{
		1,2,3
	};

	AlgorithmHelper::Intersect(set2, set1);

	REQUIRE(set2 == expectSet);
}

TEST_CASE(TAG + "Intersect-unordered_set-pair-Full") {
	unordered_set<pair<unsigned int, unsigned int>> set1{
		make_pair(1,2),
		make_pair(4,4),
		make_pair(3,4)
	};
	unordered_set<pair<unsigned int, unsigned int>> set2{
		make_pair(1,2),
		make_pair(4,4),
		make_pair(3,4)
	};
	unordered_set<pair<unsigned int, unsigned int>> expectSet{
		make_pair(1,2),
		make_pair(4,4),
		make_pair(3,4)
	};

	AlgorithmHelper::Intersect(set2, set1);

	REQUIRE(set2 == expectSet);
}

#pragma endregion

#pragma region Difference

TEST_CASE(TAG + "Difference-unordered_set-None") {
	unordered_set<unsigned int> set1{
		1,2,3
	};
	unordered_set<unsigned int> set2{
		5,6,7
	};
	unordered_set<unsigned int> expectSet{
		1,2,3
	};

	AlgorithmHelper::Difference(set1, set2);

	REQUIRE(set1 == expectSet);
}

TEST_CASE(TAG + "Difference-unordered_set-pair-None") {
	unordered_set<pair<unsigned int, unsigned int>> set1{
		make_pair(1,2),
		make_pair(3,4)
	};
	unordered_set<pair<unsigned int, unsigned int>> set2{
		make_pair(3,6),
		make_pair(7,8)
	};
	unordered_set<pair<unsigned int, unsigned int>> expectSet{
		make_pair(1,2),
		make_pair(3,4)
	};

	AlgorithmHelper::Difference(set1, set2);

	REQUIRE(set1 == expectSet);
}

TEST_CASE(TAG + "Difference-unordered_set-Single") {
	unordered_set<unsigned int> set1{
		1,2,3
	};
	unordered_set<unsigned int> set2{
		2,3
	};
	unordered_set<unsigned int> expectSet{
		1
	};

	AlgorithmHelper::Difference(set1, set2);

	REQUIRE(set1 == expectSet);
}

TEST_CASE(TAG + "Difference-unordered_set-pair-Single") {
	unordered_set<pair<unsigned int, unsigned int>> set1{
		make_pair(1,2),
		make_pair(3,4)
	};
	unordered_set<pair<unsigned int, unsigned int>> set2{
		make_pair(3,4)
	};
	unordered_set<pair<unsigned int, unsigned int>> expectSet{
		make_pair(1,2)
	};

	AlgorithmHelper::Difference(set1, set2);

	REQUIRE(set1 == expectSet);
}

TEST_CASE(TAG + "Difference-unordered_set-Multiple") {
	unordered_set<unsigned int> set1{
		1,2,3
	};
	unordered_set<unsigned int> set2{
		2,3,4
	};
	unordered_set<unsigned int> expectSet{
		1
	};

	AlgorithmHelper::Difference(set1, set2);

	REQUIRE(set1 == expectSet);
}

TEST_CASE(TAG + "Difference-unordered_set-pair-Multiple") {
	unordered_set<pair<unsigned int, unsigned int>> set1{
		make_pair(1,2),
		make_pair(4,4),
		make_pair(3,4)
	};
	unordered_set<pair<unsigned int, unsigned int>> set2{
		make_pair(4,4),
		make_pair(3,4),
		make_pair(7,8)
	};
	unordered_set<pair<unsigned int, unsigned int>> expectSet{
		make_pair(1,2)
	};

	AlgorithmHelper::Difference(set1, set2);

	REQUIRE(set1 == expectSet);
}

TEST_CASE(TAG + "Difference-unordered_set-Full") {
	unordered_set<unsigned int> set1{
		1,2,3
	};
	unordered_set<unsigned int> set2{
		1,2,3
	};
	unordered_set<unsigned int> expectSet{
	};

	AlgorithmHelper::Difference(set1, set2);

	REQUIRE(set1 == expectSet);
}

TEST_CASE(TAG + "Difference-unordered_set-pair-Full") {
	unordered_set<pair<unsigned int, unsigned int>> set1{
		make_pair(1,2),
		make_pair(4,4),
		make_pair(3,4)
	};
	unordered_set<pair<unsigned int, unsigned int>> set2{
		make_pair(1,2),
		make_pair(4,4),
		make_pair(3,4)
	};
	unordered_set<pair<unsigned int, unsigned int>> expectSet{
	};

	AlgorithmHelper::Difference(set1, set2);

	REQUIRE(set1 == expectSet);
}

#pragma endregion

#pragma region Reverse

// Expected, input
vector<pair<vector<unsigned int>, vector<unsigned int>>> ReverseTestData{
	make_pair(vector<unsigned int>{},vector<unsigned int>{}),
	make_pair(vector<unsigned int>{1},vector<unsigned int>{1}),
	make_pair(vector<unsigned int>{2,1},vector<unsigned int>{1,2}),
	make_pair(vector<unsigned int>{5,4,3,2,1},vector<unsigned int>{1,2,3,4,5}),
};

TEST_CASE(TAG + "Reverse-Tests") {
	for (int i = 0; i < ReverseTestData.size(); i++) {
		auto resultMedian = AlgorithmHelper::Reverse(ReverseTestData.at(i).second);

		REQUIRE(resultMedian == ReverseTestData.at(i).first);
	}
}

#pragma endregion

#pragma region Median

// Expected, input
const vector<pair<unsigned int, vector<unsigned int>>> MedianTestData{
	make_pair(0, vector<unsigned int>{}),
	make_pair(1, vector<unsigned int>{1}),
	make_pair(2, vector<unsigned int>{1,2}),
	make_pair(2, vector<unsigned int>{1,2,3}),
	make_pair(5, vector<unsigned int>{1,2,3,4,5,6,7,8,9}),
	make_pair(11, vector<unsigned int>{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20}),
};

TEST_CASE(TAG + "Median-Tests") {
	for (int i = 0; i < MedianTestData.size(); i++) {
		auto resultMedian = AlgorithmHelper::Median(MedianTestData.at(i).second);

		REQUIRE(resultMedian == MedianTestData.at(i).first);
	}
}

#pragma endregion

#pragma region Average

// Expected, input
const vector<pair<unsigned int, vector<unsigned int>>> AverageTestData{
	make_pair(0, vector<unsigned int>{}),
	make_pair(1, vector<unsigned int>{1}),
	make_pair(1, vector<unsigned int>{1,2}),
	make_pair(2, vector<unsigned int>{1,2,3}),
	make_pair(5, vector<unsigned int>{1,2,3,4,5,6,7,8,9}),
	make_pair(10, vector<unsigned int>{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20}),
};

TEST_CASE(TAG + "Average-Tests") {
	for (int i = 0; i < AverageTestData.size(); i++) {
		auto resultMedian = AlgorithmHelper::Average(AverageTestData.at(i).second);

		REQUIRE(resultMedian == AverageTestData.at(i).first);
	}
}

#pragma endregion


