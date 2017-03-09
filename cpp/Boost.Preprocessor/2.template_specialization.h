#ifndef TEMPLATE_SPECIALIZATION_H
#define TEMPLATE_SPECIALIZATION_H


#define BOOST_PP_VARIADICS 1    // to enable variadic version of the macros
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/cat.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/to_tuple.hpp>
#include <boost/preprocessor/seq/variadic_seq_to_seq.hpp>
#include <boost/preprocessor/tuple/size.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/to_seq.hpp>
#include <boost/preprocessor/stringize.hpp>


#define TYPE_TO_DESC_MAP                                        \
    (int,       32-bit signed integer)                          \
    (unsigned,  32-bit unsigned integer)                        \
    (float,     32-bit single precision floating point number)  \
    (double,    64-bit double precision floating point number)


#define MAP_to_seq() \
    BOOST_PP_VARIADIC_SEQ_TO_SEQ(TYPE_TO_DESC_MAP)

#define MAP_size() \
    BOOST_PP_SEQ_SIZE(MAP_to_seq())

#define MAP_nth_type(n)                     \
    BOOST_PP_TUPLE_ELEM(                    \
        0,                                  \
        BOOST_PP_SEQ_ELEM(n, MAP_to_seq())  \
    )

#define MAP_nth_desc(n)                     \
    BOOST_PP_TUPLE_ELEM(                    \
        1,                                  \
        BOOST_PP_SEQ_ELEM(n, MAP_to_seq())  \
    )


// primary template with no body.
template <typename T>
struct type_desc;


// NOTE: vertical repetition with the external spec file.
#include <boost/preprocessor/iteration/iterate.hpp>
#define BOOST_PP_FILENAME_1 "2.template_specialization_spec.h"
#define BOOST_PP_ITERATION_LIMITS (0, BOOST_PP_DEC(MAP_size()))
#include BOOST_PP_ITERATE()


/*
template <>
struct type_desc<int>
{
    constexpr static char const * value = "32-bit signed integer";
};

template <>
struct type_desc<unsigned>
{
    constexpr static char const * value = "32-bit unsigned integer";
};

...
*/


#undef MAP_to_seq
#undef MAP_size
#undef MAP_nth_type
#undef MAP_nth_desc


#endif // TEMPLATE_SPECIALIZATION_H
