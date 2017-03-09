#   define n BOOST_PP_ITERATION()

MATRIX_print_typedef(~, BOOST_PP_SEQ_ELEM(n, MATRIX_PRODUCT_SEQ))

#   undef n
