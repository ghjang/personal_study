#include <type_traits>
#include <tuple>
#include <iostream>


// basic usage example
template <typename... TypeList>
constexpr auto sizeofFuncParam(TypeList... tl)
{
    return sizeof...(TypeList);
}

template <typename... TypeList>
constexpr auto sizeofFuncParam1(TypeList... tl)
{
    return sizeof...(tl);
}


// getting the number of tuple's template parameter size.
// refer to http://en.cppreference.com/w/cpp/utility/tuple/tuple_size
template <typename... params>
constexpr auto sizeofTuple(std::tuple<params...> const&)
{
    return sizeof...(params);
}

template <typename Tuple>
struct SizeOfTuple;

template <typename... params>
struct SizeOfTuple<std::tuple<params...>>
{
    constexpr static size_t const value = sizeof...(params);
};


// getting a tuple type of which template parameters reversed to the given tuple.
template <typename Tuple, size_t SizeOfTuple, typename IndexSequence>
struct ReversedTupleImpl;

template <typename... params, size_t SizeOfTuple, size_t... i>
struct ReversedTupleImpl<std::tuple<params...>, SizeOfTuple, std::index_sequence<i...>>
{
    typedef std::tuple<
                    std::decay_t<
                        decltype(
                            std::get<SizeOfTuple - i - 1>(std::tuple<params...>())
                        )
                    >...
            > type;
};

template <typename Tuple>
struct ReversedTuple;

template <typename... params>
struct ReversedTuple<std::tuple<params...>>
{
    constexpr static int const size = sizeof...(params);
    typedef typename ReversedTupleImpl<std::tuple<params...>, size, std::make_index_sequence<size>>::type type;
};


int main() {
    // basic usage example
    static_assert(sizeofFuncParam(1, 2, 3) == 3, "");
    static_assert(sizeofFuncParam(1, 2, 3, 4, 5) == 5, "");
    static_assert(sizeofFuncParam('a', 1, 1.0, "abc") == 4, "");

    static_assert(sizeofFuncParam1(1, 2, 3) == 3, "");
    static_assert(sizeofFuncParam1(1, 2, 3, 4, 5) == 5, "");
    static_assert(sizeofFuncParam1('a', 1, 1.0, "abc") == 4, "");

    using tuple_3_t = std::tuple<int, char, std::string>;

    // getting tuple size
    tuple_3_t t = { 1, '2', "abc" };
    static_assert(sizeofTuple(t) == 3, "");
    static_assert(SizeOfTuple<tuple_3_t>::value == 3, "");

    // target reversed tuple
    using reversed_tuple_3_t = std::tuple<std::string, char, int>;

    static_assert(std::is_same<ReversedTuple<tuple_3_t>::type, reversed_tuple_3_t>::value, "");

    using reversed_tuple_3_t_1 = ReversedTuple<tuple_3_t>::type;
    static_assert(std::is_same<std::string, std::tuple_element_t<0, reversed_tuple_3_t_1>>::value, "");

    reversed_tuple_3_t_1 reversedT = { "abc", '2', 1 };
    std::cout << std::get<0>(reversedT) << std::endl;
    std::cout << std::get<1>(reversedT) << std::endl;
    std::cout << std::get<2>(reversedT) << std::endl;

    // this doesn't work. it's expected.
    //reversed_tuple_3_t_1 reversedT1 = { 1, '2', "abc" };

    return 0;
}
