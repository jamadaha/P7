#include <catch2/catch_test_macros.hpp>
#include <string>

#include "../../src/Config/config.hh"
#include "../../src/DownwardRunner/DownwardRunner.hh"

using namespace std;

const string TAG = "DownwardRunner ";
const string domain = "./TestFiles/gripper-4.pddl";
const string problem = "./TestFiles/gripper.pddl";
/*
TEST_CASE(TAG + "Run a legal domain"){
    DownwardRunner downward = DownwardRunner();
    Config config;
    auto x = downward.RunDownward(config, domain, problem);
    REQUIRE(x == DownwardRunner::DownwardRunnerResult::FoundPlan);
}

TEST_CASE(TAG + "Run impossible domain"){
    DownwardRunner downward = DownwardRunner();
    Config config;
    auto x = downward.RunDownward(config, domain, problem);
    REQUIRE(x == DownwardRunner::DownwardRunnerResult::DidNotFindPlan);
}

TEST_CASE(TAG + "Run illegal domain"){
    DownwardRunner downward = DownwardRunner();
    Config config;
    auto x = downward.RunDownward(config, domain, problem);
    REQUIRE(x == DownwardRunner::DownwardRunnerResult::None);
}
*/