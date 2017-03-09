#define n BOOST_PP_ITERATION()


template <>
struct type_desc<MAP_nth_type(n)>
{
    constexpr static char const * value = BOOST_PP_STRINGIZE(MAP_nth_desc(n));
};


#undef n
