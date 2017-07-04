#include "catch.hpp"
#include "catch_util.h"


TEST_CASE("test_case_0", "[my_test]")
{
    INFO("name: " << THIS_TEST_CASE_NAME);
    CHECK(false);
}

TEST_CASE("test_case_1", "[my_test]")
{
    INFO("name: " << THIS_TEST_CASE_NAME);
    CHECK(false);
}
