#include "catch.hpp"

#include <type_traits>
#include <string>
#include <iterator>

#include "1.function_overloading.h"


TEST_CASE("STRINGIZE", "[Boost.Preprocessor]")
{
    REQUIRE(std::strcmp(
                BOOST_PP_STRINGIZE(I want to be a string.),
                "I want to be a string."
            ) == 0);
}

TEST_CASE("CAT", "[Boost.Preprocessor]")
{
    REQUIRE(std::strcmp(
                BOOST_PP_STRINGIZE(
                    BOOST_PP_CAT(ca, t)
                ),
                "cat"
            ) == 0);
}

TEST_CASE("EXPR_IF", "[Boost.Preprocessor]")
{
    int i = 100;

#   define DECISION 1

    BOOST_PP_EXPR_IF(
        DECISION,
        i += 10;
    )

    BOOST_PP_EXPR_IF(
        BOOST_PP_NOT(DECISION),
        i *= 10;
    )

#   undef DECISION

    REQUIRE(110 == i);
}

TEST_CASE("IF", "[Boost.Preprocessor]")
{
    int i = 100;

#   define DECISION 1

    BOOST_PP_IF(
        DECISION,
        i += 10;,
        i -= 10;
    )

#   undef DECISION

    REQUIRE(110 == i);
}

TEST_CASE("INC, DEC", "[Boost.Preprocessor]")
{
    REQUIRE(11 == BOOST_PP_INC(10));
    REQUIRE(9 == BOOST_PP_DEC(10));
}

TEST_CASE("EQUAL, NOT_EQUAL", "[Boost.Preprocessor]")
{
    REQUIRE(BOOST_PP_EQUAL(10, 10));
    REQUIRE(BOOST_PP_NOT_EQUAL(10, 20));

    REQUIRE_FALSE(BOOST_PP_EQUAL(10, 20));
    REQUIRE_FALSE(BOOST_PP_NOT_EQUAL(10, 10));
}

TEST_CASE("REPEAT", "[Boost.Preprocessor]")
{
#   define PRINT_num(z, n, data) n,
#   define PRINT_num_with_sum(z, n, data) BOOST_PP_ADD(n, data),

    int num[] = {
        BOOST_PP_REPEAT(
            10,
            PRINT_num,
            ~
        )
    };
    REQUIRE(std::size(num) == 10);
    REQUIRE(0 == num[0]);
    REQUIRE(9 == num[9]);

    int num1[] = {
        BOOST_PP_REPEAT(
            10,
            PRINT_num_with_sum,
            10
        )
    };
    REQUIRE(std::size(num1) == 10);
    REQUIRE(10 == num1[0]);
    REQUIRE(19 == num1[9]);

#   undef PRINT_num_with_sum
#   undef PRINT_num
}

TEST_CASE("ENUM", "[Boost.Preprocessor]")
{
#   define PRINT_num(z, n, data) n
#   define PRINT_num_with_sum(z, n, data) BOOST_PP_ADD(n, data)

    int num[] = {
        BOOST_PP_ENUM(
            10,
            PRINT_num,
            ~
        )
    };
    REQUIRE(std::size(num) == 10);
    REQUIRE(0 == num[0]);
    REQUIRE(9 == num[9]);

    int num1[] = {
        BOOST_PP_ENUM(
            10,
            PRINT_num_with_sum,
            10
        )
    };
    REQUIRE(std::size(num1) == 10);
    REQUIRE(10 == num1[0]);
    REQUIRE(19 == num1[9]);

#   undef PRINT_num_with_sum
#   undef PRINT_num
}

TEST_CASE("ENUM_SHIFTED", "[Boost.Preprocessor]")
{
#   define PRINT_num(z, n, data) n

    int num[] = {
        BOOST_PP_ENUM_SHIFTED(
            10,
            PRINT_num,
            ~
        )
    };
    REQUIRE(std::size(num) == 9);
    REQUIRE(1 == num[0]);
    REQUIRE(9 == num[8]);

#   undef PRINT_num
}

TEST_CASE("ENUM_TRAILINIG", "[Boost.Preprocessor]")
{
#   define PRINT_num(z, n, data) n

    int num[] = {
        10000
        BOOST_PP_ENUM_TRAILING(
            10,
            PRINT_num,
            ~
        )
    };
    REQUIRE(std::size(num) == 11);
    REQUIRE(10000 == num[0]);
    REQUIRE(9 == num[10]);

#   undef PRINT_num
}

TEST_CASE("ENUM_PARAMS", "[Boost.Preprocessor]")
{
    int num[] = {
        BOOST_PP_ENUM_PARAMS(
            10,
            10
        )
    };
    REQUIRE(std::size(num) == 10);
    REQUIRE(100 == num[0]);
    REQUIRE(109 == num[9]);

    int BOOST_PP_ENUM_PARAMS(
            10,
            var
    );
    REQUIRE((std::is_same<
                    int,
                    decltype(var9)
            >::value));

    // NOTE: there are also ENUM_TRAILING_PARAMS and ENUM_SHIFTED_PARAMS macros.
}


TEST_CASE("sum", "[function overloading]")
{
    REQUIRE(sum(1, 2, 3, 4, 5) == 15);

    REQUIRE(sum_o(1, 2, 3, 4, 5) == 15);
}
