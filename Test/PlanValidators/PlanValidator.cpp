#include <catch2/catch_test_macros.hpp>

#include "../../src/PlanValidators/PlanValidator.h"
#include "../../src/Helpers/FileHelper.h"

using namespace std;

const string TAG = "PlanValidator ";
const string domainFile = "./TestFiles/gripper.pddl";
const string problemFile = "./TestFiles/gripper-4.pddl";
const string goodPlan = "./TestFiles/good_plan";
const string badPlan = "./TestFiles/bad_plan";
const filesystem::path validatorPath = filesystem::path("/root/downward-projects/VAL/validate");

TEST_CASE(TAG + "ValidateGoodPlan") {
    if (!FileHelper::DoesFileExist(validatorPath)) {
        WARN("Cannot run PlanValidator test. VAL was not found! Skipping test...");
    }
    else {
        Config config;
        config.validatorPath = validatorPath;

        PlanValidator validator;
        PlanValidator::ValidatorResult res = validator.ValidatePlan(config, domainFile, problemFile, goodPlan);
        REQUIRE(PlanValidator::ValidatorResult::PlanMatch == res);
    }
}

TEST_CASE(TAG + "ValidateBadPlan") {
    if (!FileHelper::DoesFileExist(validatorPath)) {
        WARN("Cannot run PlanValidator test. VAL was not found! Skipping test...");
    }
    else {
        Config config;
        config.validatorPath = validatorPath;

        PlanValidator validator;
        PlanValidator::ValidatorResult res = validator.ValidatePlan(config, domainFile, problemFile, badPlan);
        REQUIRE(PlanValidator::ValidatorResult::PlanNotMatch == res);
    }
}

TEST_CASE(TAG + "MissingDomainFile") {
    PlanValidator validator;
    PlanValidator::ValidatorResult res = validator.ValidatePlan(Config(), "none", problemFile, badPlan);
    REQUIRE(PlanValidator::ValidatorResult::MissingDomainFile == res);
}

TEST_CASE(TAG + "MissingProblemFile") {
    PlanValidator validator;
    PlanValidator::ValidatorResult res = validator.ValidatePlan(Config(), domainFile, "none", badPlan);
    REQUIRE(PlanValidator::ValidatorResult::MissingProblemFile == res);
}

TEST_CASE(TAG + "MissingPlanFile") {
    PlanValidator validator;
    PlanValidator::ValidatorResult res = validator.ValidatePlan(Config(), domainFile, problemFile, "none");
    REQUIRE(PlanValidator::ValidatorResult::MissingPlanFile == res);
}