#include <catch2/catch_test_macros.hpp>

#include "../../src/Helpers/Hashes.hh"

using namespace std;
const string TAG = "Helpers - Hashes ";

#ifndef NDEBUG
const int iterationsToRunAll = 100;
#else
const int iterationsToRunAll = 100000;
#endif

#pragma region vector<unsigned int>

TEST_CASE(TAG + "vector<unsigned int>-Small") {
	srand(time(NULL));
	const int iterationsToRun = iterationsToRunAll;
	const int randomNumbersToMake = 1;
	for (int i = 0; i < iterationsToRun; i++) {
		vector<unsigned int> v1;
		vector<unsigned int> v2;
		for (int j = 0; j < randomNumbersToMake; j++) {
			v1.push_back(rand());
			v2.push_back(rand());
		}

		if (v1 != v2)
			REQUIRE(hash<vector<unsigned int>>{}(v1) != hash<vector<unsigned int>>{}(v2));
		else
			REQUIRE(hash<vector<unsigned int>>{}(v1) == hash<vector<unsigned int>>{}(v2));
	}
}

TEST_CASE(TAG + "vector<unsigned int>-Medium") {
	srand(time(NULL));
	const int iterationsToRun = iterationsToRunAll;
	const int randomNumbersToMake = 5;
	for (int i = 0; i < iterationsToRun; i++) {
		vector<unsigned int> v1;
		vector<unsigned int> v2;
		for (int j = 0; j < randomNumbersToMake; j++) {
			v1.push_back(rand());
			v2.push_back(rand());
		}

		if (v1 != v2)
			REQUIRE(hash<vector<unsigned int>>{}(v1) != hash<vector<unsigned int>>{}(v2));
		else
			REQUIRE(hash<vector<unsigned int>>{}(v1) == hash<vector<unsigned int>>{}(v2));
	}
}

TEST_CASE(TAG + "vector<unsigned int>-Large") {
	srand(time(NULL));
	const int iterationsToRun = iterationsToRunAll;
	const int randomNumbersToMake = 50;
	for (int i = 0; i < iterationsToRun; i++) {
		vector<unsigned int> v1;
		vector<unsigned int> v2;
		for (int j = 0; j < randomNumbersToMake; j++) {
			v1.push_back(rand());
			v2.push_back(rand());
		}

		if (v1 != v2)
			REQUIRE(hash<vector<unsigned int>>{}(v1) != hash<vector<unsigned int>>{}(v2));
		else
			REQUIRE(hash<vector<unsigned int>>{}(v1) == hash<vector<unsigned int>>{}(v2));
	}
}

TEST_CASE(TAG + "vector<unsigned int>-Huge") {
	srand(time(NULL));
	const int iterationsToRun = iterationsToRunAll;
	const int randomNumbersToMake = 5000;
	for (int i = 0; i < iterationsToRun; i++) {
		vector<unsigned int> v1;
		vector<unsigned int> v2;
		for (int j = 0; j < randomNumbersToMake; j++) {
			v1.push_back(rand());
			v2.push_back(rand());
		}

		if (v1 != v2)
			REQUIRE(hash<vector<unsigned int>>{}(v1) != hash<vector<unsigned int>>{}(v2));
		else
			REQUIRE(hash<vector<unsigned int>>{}(v1) == hash<vector<unsigned int>>{}(v2));
	}
}

#pragma endregion

#pragma region unordered_set<unsigned int>

TEST_CASE(TAG + "unordered_set<unsigned int>-Small") {
	srand(time(NULL));
	const int iterationsToRun = iterationsToRunAll;
	const int randomNumbersToMake = 1;
	for (int i = 0; i < iterationsToRun; i++) {
		unordered_set<unsigned int> v1;
		unordered_set<unsigned int> v2;
		for (int j = 0; j < randomNumbersToMake; j++) {
			v1.emplace(rand());
			v2.emplace(rand());
		}

		if (v1 != v2)
			REQUIRE(hash<unordered_set<unsigned int>>{}(v1) != hash<unordered_set<unsigned int>>{}(v2));
		else
			REQUIRE(hash<unordered_set<unsigned int>>{}(v1) == hash<unordered_set<unsigned int>>{}(v2));
	}
}

TEST_CASE(TAG + "unordered_set<unsigned int>-Medium") {
	srand(time(NULL));
	const int iterationsToRun = iterationsToRunAll;
	const int randomNumbersToMake = 5;
	for (int i = 0; i < iterationsToRun; i++) {
		unordered_set<unsigned int> v1;
		unordered_set<unsigned int> v2;
		for (int j = 0; j < randomNumbersToMake; j++) {
			v1.emplace(rand());
			v2.emplace(rand());
		}

		if (v1 != v2)
			REQUIRE(hash<unordered_set<unsigned int>>{}(v1) != hash<unordered_set<unsigned int>>{}(v2));
		else
			REQUIRE(hash<unordered_set<unsigned int>>{}(v1) == hash<unordered_set<unsigned int>>{}(v2));
	}
}

TEST_CASE(TAG + "unordered_set<unsigned int>-Large") {
	srand(time(NULL));
	const int iterationsToRun = iterationsToRunAll;
	const int randomNumbersToMake = 50;
	for (int i = 0; i < iterationsToRun; i++) {
		unordered_set<unsigned int> v1;
		unordered_set<unsigned int> v2;
		for (int j = 0; j < randomNumbersToMake; j++) {
			v1.emplace(rand());
			v2.emplace(rand());
		}

		if (v1 != v2)
			REQUIRE(hash<unordered_set<unsigned int>>{}(v1) != hash<unordered_set<unsigned int>>{}(v2));
		else
			REQUIRE(hash<unordered_set<unsigned int>>{}(v1) == hash<unordered_set<unsigned int>>{}(v2));
	}
}

TEST_CASE(TAG + "unordered_set<unsigned int>-Huge") {
	srand(time(NULL));
	const int iterationsToRun = iterationsToRunAll;
	const int randomNumbersToMake = 5000;
	for (int i = 0; i < iterationsToRun; i++) {
		unordered_set<unsigned int> v1;
		unordered_set<unsigned int> v2;
		for (int j = 0; j < randomNumbersToMake; j++) {
			v1.emplace(rand());
			v2.emplace(rand());
		}

		if (v1 != v2)
			REQUIRE(hash<unordered_set<unsigned int>>{}(v1) != hash<unordered_set<unsigned int>>{}(v2));
		else
			REQUIRE(hash<unordered_set<unsigned int>>{}(v1) == hash<unordered_set<unsigned int>>{}(v2));
	}
}

#pragma endregion

#pragma region pair<unsigned int, unsigned int>

TEST_CASE(TAG + "pair<unsigned int, unsigned int>") {
	srand(time(NULL));
	const int iterationsToRun = iterationsToRunAll;
	for (int i = 0; i < iterationsToRun; i++) {
		pair<unsigned int, unsigned int> v1 = make_pair(rand(), rand());
		pair<unsigned int, unsigned int> v2 = make_pair(rand(), rand());

		if (v1 != v2)
			REQUIRE(hash<pair<unsigned int, unsigned int>>{}(v1) != hash<pair<unsigned int, unsigned int>>{}(v2));
		else
			REQUIRE(hash<pair<unsigned int, unsigned int>>{}(v1) == hash<pair<unsigned int, unsigned int>>{}(v2));
	}
}

#pragma endregion

#pragma region pair<unsigned int*, unsigned int*>

TEST_CASE(TAG + "pair<unsigned int*, unsigned int*>") {
	srand(time(NULL));
	const int iterationsToRun = iterationsToRunAll;
	for (int i = 0; i < iterationsToRun; i++) {
		unsigned int a1 = rand();
		unsigned int a2 = rand();
		unsigned int a3 = rand();
		unsigned int a4 = rand();

		pair<unsigned int*, unsigned int*> v1 = make_pair(&a1, &a2);
		pair<unsigned int*, unsigned int*> v2 = make_pair(&a3, &a4);

		if (v1 != v2)
			REQUIRE(hash<pair<unsigned int*, unsigned int*>>{}(v1) != hash<pair<unsigned int*, unsigned int*>>{}(v2));
		else
			REQUIRE(hash<pair<unsigned int*, unsigned int*>>{}(v1) == hash<pair<unsigned int*, unsigned int*>>{}(v2));
	}
}

#pragma endregion

