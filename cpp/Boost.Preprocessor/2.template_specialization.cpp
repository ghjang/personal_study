#include "catch.hpp"

#include <type_traits>
#include <cstring>

#include "2.template_specialization.h"


TEST_CASE("SEQ_SIZE", "[Boost.Preprocessor]")
{
    REQUIRE(5 == BOOST_PP_SEQ_SIZE(
                    (a)(b)(c)(d)(f)
                 ));

    REQUIRE(5 == BOOST_PP_SEQ_SIZE(
                    (a + 1)(b - 1)(c;)(d += 1)(f)
                 ));
}

TEST_CASE("SEQ_ELEM", "[Boost.Preprocessor]")
{
    REQUIRE(std::strcmp(
                BOOST_PP_STRINGIZE(
                    BOOST_PP_SEQ_ELEM(
                        2,
                        (a)(b)(c)(d)(f)
                    )
                ),
                "c"
            ) == 0);

    REQUIRE(std::strcmp(
                BOOST_PP_STRINGIZE(
                    BOOST_PP_SEQ_ELEM(
                        3,
                        (a + 1)(b - 1)(c;)(d += 1)(f)
                    )
                ),
                "d += 1"
            ) == 0);
}

TEST_CASE("SEQ_FOR_EACH", "[Boost.Preprocessor]")
{
#   define PRINT_with_suffix(r, data, elem) \
        int BOOST_PP_CAT(elem, data);

    BOOST_PP_SEQ_FOR_EACH(
        PRINT_with_suffix,
        _s,
        (a)(b)(c)
    )

    REQUIRE((std::is_same<
                    int,
                    decltype(c_s)
            >::value));

#   undef PRINT_with_suffix
}

TEST_CASE("SEQ_CAT", "[Boost.Preprocessor]")
{
    REQUIRE(std::strcmp(
                BOOST_PP_STRINGIZE(
                    BOOST_PP_SEQ_CAT(
                        (a)(a + b)(b + c)
                    )
                ),
                "aa + bb + c"
            ) == 0);
}

TEST_CASE("TUPLE_SIZE", "[Boost.Preprocessor]")
{
    REQUIRE(3 == BOOST_PP_TUPLE_SIZE(
                        (a, b, c)
                 ));

    REQUIRE(3 == BOOST_PP_TUPLE_SIZE(
                        (a, b + 10, c += 10;)
                 ));
}

TEST_CASE("TUPLE_ELEM", "[Boost.Preprocessor]")
{
    REQUIRE(std::strcmp(
                BOOST_PP_STRINGIZE(
                    BOOST_PP_TUPLE_ELEM(
                        2,
                        (a, b, c)
                    )
                ),
                "c"
            ) == 0);

    REQUIRE(std::strcmp(
                BOOST_PP_STRINGIZE(
                    BOOST_PP_TUPLE_ELEM(
                        2,
                        (a, b + 10, c += 10;)
                    )
                ),
                "c += 10;"
            ) == 0);
}

TEST_CASE("SEQ_TO_TUPLE", "[Boost.Preprocessor]")
{
    REQUIRE(std::strcmp(
                BOOST_PP_STRINGIZE(
                    BOOST_PP_SEQ_TO_TUPLE(
                        (a)(b)(c)
                    )
                ),
                "(a, b, c)"
            ) == 0);
}

TEST_CASE("TUPLE_TO_SEQ", "[Boost.Preprocessor]")
{
    REQUIRE(std::strcmp(
                BOOST_PP_STRINGIZE(
                    BOOST_PP_TUPLE_TO_SEQ(
                        (a, b, c)
                    )
                ),
                "(a)(b)(c)"
            ) == 0);
}

TEST_CASE("VARIADIC_SEQ_TO_SEQ", "[Boost.Preprocessor]")
{
    REQUIRE(std::strcmp(
                BOOST_PP_STRINGIZE(
                    BOOST_PP_VARIADIC_SEQ_TO_SEQ(
                        (a, b)(c, d)(1, 2, 3)
                    )
                ),
                "((a, b)) ((c, d)) ((1, 2, 3))"
            ) == 0);
}

TEST_CASE("type_desc", "[template specialization]")
{
    REQUIRE(std::strcmp(
                type_desc<int>::value,
                "32-bit signed integer"
            ) == 0);

    REQUIRE(std::strcmp(
                type_desc<double>::value,
                "64-bit double precision floating point number"
            ) == 0);
}
