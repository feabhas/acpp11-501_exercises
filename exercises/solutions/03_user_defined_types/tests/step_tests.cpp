// This test suite provides coverage for:

// * Default construction
// * Valid step creation with different types
// * Duration validation
// * Type validation
// * String conversion for all step types
// * Validity checking for all step types and durations
//
// The tests use doctest's SUBCASE feature to organize related tests 
// and make the output more readable. 
// The test cases verify both valid and invalid scenarios, 
// and check all possible step types defined in the enum class.

#define DOCTEST_CONFIG_NO_MULTITHREADING
#define DOCTEST_CONFIG_NO_POSIX_SIGNALS
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Step.h"

using namespace WMS;

TEST_CASE("Default constructed Step") {
    Step step{};
    CHECK(step.get_type() == Step::Type::invalid);
    CHECK(step.get_duration() == 0);
    CHECK_FALSE(step.is_valid());
}

TEST_CASE("Constructing valid steps") {
    SUBCASE("Fill step") {
        Step step{Step::Type::fill, 10};
        CHECK(step.get_type() == Step::Type::fill);
        CHECK(step.get_duration() == 10);
        CHECK(step.is_valid());
    }

    SUBCASE("Wash step") {
        Step step{Step::Type::wash, 30};
        CHECK(step.get_type() == Step::Type::wash);
        CHECK(step.get_duration() == 30);
        CHECK(step.is_valid());
    }
}

TEST_CASE("String conversion") {
    SUBCASE("Invalid step") {
        Step step{};
        CHECK_EQ(step.to_string(), "invalid");
    }

    SUBCASE("All valid step types") {
        const std::pair<Step::Type, const char*> test_cases[] = {
            {Step::Type::empty, "empty"},
            {Step::Type::fill, "fill"},
            {Step::Type::heat, "heat"},
            {Step::Type::wash, "wash"},
            {Step::Type::rinse, "rinse"},
            {Step::Type::spin, "spin"},
            {Step::Type::dry, "dry"},
            {Step::Type::complete, "complete"}
        };

        for (const auto& [type, expected] : test_cases) {
            Step step{type, 1};
            CHECK_EQ(step.to_string(), expected);
        }
    }
}

TEST_CASE("Step validity") {
    SUBCASE("Valid steps") {
        const Step::Type valid_types[] = {
            Step::Type::empty, Step::Type::fill, Step::Type::heat,
            Step::Type::wash, Step::Type::rinse, Step::Type::spin,
            Step::Type::dry, Step::Type::complete
        };

        for (auto type : valid_types) {
            Step step{type, 1};
            CHECK(step.is_valid());
        }
    }

    SUBCASE("Invalid duration") {
        Step step{Step::Type::wash, 0};
        CHECK_FALSE(step.is_valid());
    }
}