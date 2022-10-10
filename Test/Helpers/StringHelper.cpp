#include <catch2/catch_test_macros.hpp>

#include "../../src/Helpers/StringHelper.h"

using namespace std;
const string TAG = "StringHelper ";

#pragma region RemoveCharacter

TEST_CASE(TAG + "RemoveCharacter_Single1") {
    string line = "a b c d/(2";
    string expectedLine = " b c d/(2";
    StringHelper::RemoveCharacter(&line, 'a');
    REQUIRE(line == expectedLine);
}

TEST_CASE(TAG + "RemoveCharacter_Single2") {
    string line = "a b c d/(2";
    string expectedLine = "abcd/(2";
    StringHelper::RemoveCharacter(&line, ' ');
    REQUIRE(line == expectedLine);
}

TEST_CASE(TAG + "RemoveCharacter_Single3") {
    string line = "a b c d/(2";
    string expectedLine = "a b  d/(2";
    StringHelper::RemoveCharacter(&line, 'c');
    REQUIRE(line == expectedLine);
}

TEST_CASE(TAG + "RemoveCharacter_Multiple1") {
    string line = "a b c d/(2";
    string expectedLine = "   d/(2";
    StringHelper::RemoveCharacter(&line, 'a');
    StringHelper::RemoveCharacter(&line, 'b');
    StringHelper::RemoveCharacter(&line, 'c');
    REQUIRE(line == expectedLine);
}

TEST_CASE(TAG + "RemoveCharacter_Multiple2") {
    string line = "a b c d/(2";
    string expectedLine = "d/(2";
    StringHelper::RemoveCharacter(&line, 'a');
    StringHelper::RemoveCharacter(&line, 'b');
    StringHelper::RemoveCharacter(&line, 'c');
    StringHelper::RemoveCharacter(&line, ' ');
    REQUIRE(line == expectedLine);
}

#pragma endregion

TEST_CASE(TAG + "Trim_Single1") {
    string line = " text text ";
    string expectedLine = "text text";
    line = StringHelper::Trim(line);
    REQUIRE(line == expectedLine);
}

TEST_CASE(TAG + "Trim_Single2") {
    string line = "      text text ";
    string expectedLine = "text text";
    line = StringHelper::Trim(line);
    REQUIRE(line == expectedLine);
}

TEST_CASE(TAG + "Trim_Single3") {
    string line = "      text text                    ";
    string expectedLine = "text text";
    line = StringHelper::Trim(line);
    REQUIRE(line == expectedLine);
}
