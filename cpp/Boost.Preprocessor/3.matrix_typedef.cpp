#include "catch.hpp"

#include <cstring>

#include "3.matrix_typedef.h"


TEST_CASE("SEQ_FIRST_N", "[Boost.Preprocessor]")
{
    REQUIRE(std::strcmp(
                BOOST_PP_STRINGIZE(
                    BOOST_PP_SEQ_FIRST_N(
                        2,
                        (a)(b)(c)(d)(e)
                    )
                ),
                "(a) (b)"
            ) == 0);
}

TEST_CASE("SEQ_FOR_EACH_PRODUCT", "[Boost.Preprocessor]")
{
#   define SETS         \
        ((a)(b)(c))     \
        ((1)(2))        \
        ((_s)(_z))

#   define PRINT_to_tuple(r, product) BOOST_PP_SEQ_TO_TUPLE(product)

    REQUIRE(std::strcmp(
                BOOST_PP_STRINGIZE(
                    BOOST_PP_SEQ_HEAD(
                        BOOST_PP_VARIADIC_SEQ_TO_SEQ(
                            BOOST_PP_SEQ_FOR_EACH_PRODUCT(
                                PRINT_to_tuple,
                                SETS
                            )
                        )
                    )
                ),
                "(a, 1, _s)"
            ) == 0);

#   undef PRINT_to_tuple
#   undef SETS
}
