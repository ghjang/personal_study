#include <type_traits>
#include <utility>
#include <iostream>


constexpr int IdentityInt(int i) { return i; }

constexpr int SquareInt(int i) { return i * i; }

template <std::size_t i>
struct SquareIntGenerator
{
    constexpr static std::size_t value = SquareInt(i);
};

constexpr int Factorial(int i)
{
    if (i == 0) {
        return 1;
    }
    return i * Factorial(i - 1);
}

template <std::size_t i>
struct FactorialGenerator
{
    constexpr static std::size_t value = Factorial(i);
};


template <typename IndexSequence>
struct SquareIntegerSequenceImpl;

template <std::size_t... i>
struct SquareIntegerSequenceImpl<std::integer_sequence<std::size_t, i...>>
{
    using type = std::integer_sequence<std::size_t, SquareInt(i)...>;
};

template <std::size_t i>
struct SquareIntegerSequence
        : SquareIntegerSequenceImpl<std::make_index_sequence<i>>
{ };


template <typename IndexSequence, template<std::size_t> class GeneratorFunc>
struct CustomIntegerSequenceImpl;

template <std::size_t... i, template<std::size_t> class GeneratorFunc>
struct CustomIntegerSequenceImpl<
            std::integer_sequence<std::size_t, i...>,
            GeneratorFunc
        >
{
    using type = std::integer_sequence<std::size_t, GeneratorFunc<i>::value...>;
};

template <std::size_t i, template<std::size_t> class GeneratorFunc>
struct CustomIntegerSequence
        : CustomIntegerSequenceImpl<std::make_index_sequence<i>, GeneratorFunc>
{ };

template <std::size_t i, template<std::size_t> class GeneratorFunc>
using MakeCustomIntegerSequence = typename CustomIntegerSequence<i, GeneratorFunc>::type;


// NOTE: This is possible if 'f' could be wrapped as a constant expression. (???)
/*
template <std::size_t... i, typename Ret, typename Arg>
constexpr auto MakeCustomIntegerSequenceImpl(std::integer_sequence<std::size_t, i...>, Ret f(Arg))
{
    return std::integer_sequence<std::size_t, f(i)...>();
}

template <std::size_t i, typename Ret, typename Arg>
constexpr auto MakeCustomIntegerSequence(std::integral_constant<std::size_t, i>, Ret f(Arg))
{
    return MakeCustomIntegerSequenceImpl(std::make_index_sequence<i>(), f);
}
*/


int main() {
    using std::is_same;
    using std::integral_constant;
    using std::integer_sequence;
    using std::make_integer_sequence;
    using std::make_index_sequence;

    // basic usage
    {
        using int_seq = make_integer_sequence<std::size_t, 3>;
        using index_seq = make_index_sequence<3>;
        static_assert(is_same<integer_sequence<std::size_t, 0, 1, 2>, int_seq>(), "");
        static_assert(is_same<integer_sequence<std::size_t, 0, 1, 2>, index_seq>(), "");
        static_assert(is_same<int_seq, index_seq>(), "");
    }

    // combination with constexpr functions
    {
        using identity_int_seq = integer_sequence<int, IdentityInt(0), IdentityInt(1), IdentityInt(2)>;
        static_assert(is_same<integer_sequence<int, 0, 1, 2>, identity_int_seq>(), "");

        using square_int_seq = integer_sequence<int, SquareInt(0), SquareInt(1), SquareInt(2), SquareInt(3)>;
        static_assert(is_same<integer_sequence<int, 0, 1, 4, 9>, square_int_seq>(), "");
    }

    // a custom integer sequence example
    {
        using square_int_seq = typename SquareIntegerSequence<4>::type;
        static_assert(is_same<integer_sequence<std::size_t, 0, 1, 4, 9>, square_int_seq>(), "");
    }

    // another custom integer sequence example. This is more generic. :-)
    {
        using square_int_seq = typename CustomIntegerSequence<4, SquareIntGenerator>::type;
        static_assert(is_same<integer_sequence<std::size_t, 0, 1, 4, 9>, square_int_seq>(), "");

        using square_int_seq_1 = MakeCustomIntegerSequence<4, SquareIntGenerator>;
        static_assert(is_same<integer_sequence<std::size_t, 0, 1, 4, 9>, square_int_seq_1>(), "");
        static_assert(is_same<square_int_seq, square_int_seq_1>(), "");
    }

    // factorial custom integer sequence example.
    {
        using factorial_int_seq = MakeCustomIntegerSequence<5, FactorialGenerator>;
        static_assert(is_same<integer_sequence<std::size_t, 1, 1, 2, 6, 24>, factorial_int_seq>(), "");
    }

    // NOTE: This is possible if 'SquareInt' could be wrapped as a constant expression. (???)
    {
        /*
        static_assert(is_same<
                            integer_sequence<std::size_t, 0, 1, 4, 9>,
                            decltype(MakeCustomIntegerSequence(integral_constant<std::size_t, 4>(), &SquareInt))
                        >(), "");
        */
    }

    return 0;
}

