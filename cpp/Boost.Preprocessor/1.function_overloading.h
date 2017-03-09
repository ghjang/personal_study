#ifndef FUNCTION_OVERLOADING_H
#define FUNCTION_OVERLOADING_H


#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/control/expr_if.hpp>
#include <boost/preprocessor/logical/not.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/arithmetic/add.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/comparison/not_equal.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_shifted.hpp>
#include <boost/preprocessor/repetition/enum_trailing.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/stringize.hpp>


//==============================================================================
template <typename... T>
auto sum(T... args)
{
    // C++17 fold expression. fold-left.
    return (... + args);
}


//==============================================================================
#ifndef MAX_SUM_FUNCTION_ARG_COUNT
#   define MAX_SUM_FUNCTION_ARG_COUNT 10
#endif

#define SUM_print_arg(z, n, data)   \
    BOOST_PP_CAT(T, n) BOOST_PP_CAT(arg, n)

#define SUM_print_body(z, n, data)  \
    BOOST_PP_CAT(arg, n) +

#define SUM_function_overload(z, n, data)               \
    BOOST_PP_EXPR_IF(                                   \
        BOOST_PP_NOT_EQUAL(n, 0),                       \
        template <                                      \
    )                                                   \
    BOOST_PP_ENUM_PARAMS(n, typename T)                 \
    BOOST_PP_EXPR_IF(                                   \
        BOOST_PP_NOT_EQUAL(n, 0),                       \
        >                                               \
    )                                                   \
    auto sum_o(BOOST_PP_ENUM(n, SUM_print_arg, ~))      \
    {                                                   \
        return BOOST_PP_REPEAT(                         \
                    n,                                  \
                    SUM_print_body,                     \
                    ~                                   \
               ) 0;                                     \
    }

#define DEFINE_SUM_FUNCTION()                           \
    BOOST_PP_REPEAT(                                    \
        BOOST_PP_INC(MAX_SUM_FUNCTION_ARG_COUNT),       \
        SUM_function_overload,                          \
        ~                                               \
    )


// NOTE: This is an example of horizontal repetition.
DEFINE_SUM_FUNCTION()


/*
auto sum_o()
{ return 0; }

template < typename T0 >
auto sum_o( T0 arg0)
{ return arg0 + 0; }

template < typename T0 , typename T1 >
auto sum_o( T0 arg0 , T1 arg1)
{ return arg0 + arg1 + 0; }

template < typename T0 , typename T1 , typename T2 >
auto sum_o( T0 arg0 , T1 arg1 , T2 arg2)
{ return arg0 + arg1 + arg2 + 0; }

...
*/


#undef DEFINE_SUM_FUNCTION
#undef SUM_function_overload
#undef SUM_print_body
#undef SUM_print_arg
#undef MAX_SUM_FUNCTION_ARG_COUNT


#endif // FUNCTION_OVERLOADING_H
