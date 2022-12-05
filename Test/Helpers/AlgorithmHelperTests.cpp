#include <catch2/catch_test_macros.hpp>

#include <vector>
#include <unordered_set>

#include "../../src/Helpers/AlgorithmHelper.hh"
#include "../../src/Helpers/Hashes.hh"

using namespace std;
const string TAG = "AlgorithmHelper ";

#pragma region InsertAll Tests

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

