#ifndef BOOST_PP_IS_ITERATING


#   ifndef MATRIX_TYPEDEF_H
#   define MATRIX_TYPEDEF_H


#   define BOOST_PP_VARIADICS 1    // to enable variadic version of the macros
#   include <boost/preprocessor/cat.hpp>
#   include <boost/preprocessor/repetition/enum.hpp>
#   include <boost/preprocessor/repetition/enum_shifted.hpp>
#   include <boost/preprocessor/repetition/enum_trailing.hpp>
#   include <boost/preprocessor/seq/size.hpp>
#   include <boost/preprocessor/seq/elem.hpp>
#   include <boost/preprocessor/seq/cat.hpp>
#   include <boost/preprocessor/seq/seq.hpp>
#   include <boost/preprocessor/seq/first_n.hpp>
#   include <boost/preprocessor/seq/for_each_product.hpp>
#   include <boost/preprocessor/seq/to_tuple.hpp>
#   include <boost/preprocessor/seq/variadic_seq_to_seq.hpp>
#   include <boost/preprocessor/tuple/elem.hpp>
#   include <boost/preprocessor/tuple/to_seq.hpp>
#   include <boost/preprocessor/arithmetic/inc.hpp>
#   include <boost/preprocessor/arithmetic/dec.hpp>
#   include <boost/preprocessor/stringize.hpp>


#   include "utility.h"


#   define MATRIX_type_to_suffix_map                       \
       (float,         f)                                  \
       (double,        d)

#   define MATRIX_type_to_suffix_tuple_seq                 \
       BOOST_PP_VARIADIC_SEQ_TO_SEQ(                       \
           MATRIX_type_to_suffix_map                       \
       )

#   define MATRIX_print_index(z, n, data) n

#   define MATRIX_index_tuple(size)                        \
       (BOOST_PP_ENUM_SHIFTED(                             \
           BOOST_PP_INC(size),                             \
           MATRIX_print_index,                             \
           ~                                               \
       ))

#   define MATRIX_index_seq(size)                          \
       BOOST_PP_TUPLE_TO_SEQ(MATRIX_index_tuple(size))

#   define MATRIX_set_seq(row, col, tupleSeq)              \
       (MATRIX_index_seq(row))                             \
       (MATRIX_index_seq(col))                             \
       (tupleSeq)

#   define MATRIX_cat_suffix(product)                      \
       BOOST_PP_CAT(                                       \
           BOOST_PP_SEQ_CAT(                               \
               BOOST_PP_SEQ_FIRST_N(2, product)            \
           ),                                              \
           BOOST_PP_TUPLE_ELEM(                            \
               1,                                          \
               BOOST_PP_SEQ_ELEM(2, product)               \
           )                                               \
       )

#   define MATRIX_print_size_param(z, n, seq)              \
       BOOST_PP_SEQ_ELEM(n, seq)

#   define MATRIX_gen_type(product)                        \
       Matx<                                               \
       BOOST_PP_TUPLE_ELEM(                                \
           0,                                              \
           BOOST_PP_SEQ_ELEM(2, product)                   \
       )                                                   \
       BOOST_PP_ENUM_TRAILING(                             \
           2,                                              \
           MATRIX_print_size_param,                        \
           product                                         \
       )                                                   \
       >


#   define MATRIX_print_typedef(r, product)                \
       BOOST_PP_CAT(                                       \
           using Matx,                                     \
           MATRIX_cat_suffix(product)                      \
       ) = MATRIX_gen_type(product);

#   define DEFINE_MATRIX_TYPEDEF(row, col)                 \
       BOOST_PP_SEQ_FOR_EACH_PRODUCT(                      \
           MATRIX_print_typedef,                           \
           MATRIX_set_seq(                                 \
               row,                                        \
               col,                                        \
               MATRIX_type_to_suffix_tuple_seq             \
           )                                               \
       )


//MATRIX_type_to_suffix_tuple_seq
//MATRIX_index_tuple(6)
//MATRIX_index_seq(6)
//MATRIX_set_seq(6, 6, MATRIX_type_to_suffix_tuple_seq)


// NOTE: horizontal repetition
DEFINE_MATRIX_TYPEDEF(6, 6)


#   define MATRIX_print_product(r, product)    \
       (product)

#   define MATRIX_print_product_seq(row, col)      \
       BOOST_PP_SEQ_FOR_EACH_PRODUCT(              \
           MATRIX_print_product,                   \
           MATRIX_set_seq(                         \
               row,                                \
               col,                                \
               MATRIX_type_to_suffix_tuple_seq     \
           )                                       \
       )


#   define MATRIX_PRODUCT_SEQ MATRIX_print_product_seq(6, 6)


// vertical repetition. self-iteration. It's very slow to be preprocessed.
/*
#   include <boost/preprocessor/iteration/iterate.hpp>
#   define BOOST_PP_ITERATION_LIMITS (0, BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(MATRIX_PRODUCT_SEQ)))
#   define BOOST_PP_FILENAME_1  "3.matrix_typedef.h"    // this file
#   include BOOST_PP_ITERATE()
*/

// NOTE: vertical repetition. file iteration. It seems to be even slower than the self-iteration.
/*
#   include <boost/preprocessor/iteration/iterate.hpp>
#   define BOOST_PP_ITERATION_LIMITS (0, BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(MATRIX_PRODUCT_SEQ)))
#   define BOOST_PP_FILENAME_1  "3.matrix_typedef_spec.h"    // spec file
#   include BOOST_PP_ITERATE()
*/

#   endif // MATRIX_TYPEDEF_H


#else // BOOST_PP_IS_ITERATING


#   define n BOOST_PP_ITERATION()


    MATRIX_print_typedef(~, BOOST_PP_SEQ_ELEM(n, MATRIX_PRODUCT_SEQ))

/*
    using Matx11f = Matx< float , 1 , 1 >;
    using Matx11d = Matx< double , 1 , 1 >;
    using Matx12f = Matx< float , 1 , 2 >;
    using Matx12d = Matx< double , 1 , 2 >;
    using Matx13f = Matx< float , 1 , 3 >;
    using Matx13d = Matx< double , 1 , 3 >;
    ...
*/

#   undef n


#endif // BOOST_PP_IS_ITERATING
