#include <type_traits>
#include <ratio>
#include <utility>

// doesn't exist. why?
//#include <experimental/numeric>

#include <cassert>
#include <iostream>


constexpr uint8_t get_number_of_digit(intmax_t i)
{
    if (i < 0) {
        i = -i;
    }
    if (i < 10) {
        return 1;
    }
    uint8_t n = 1;
    for ( ; ; ) {
        ++n;
        if (i / 10 < 10) {
            break;
        }
        i /= 10;
    }
    return n;
}

constexpr char get_digit_char(intmax_t n, uint8_t numOfDigit, uint8_t digitIndex)
{
    intmax_t modNum = 1;
    for (uint8_t i = 0; i < digitIndex; ++i) {
        modNum *= 10;
    }
    n %= modNum;

    for (uint8_t i = 0; i < digitIndex - 1; ++i) {
        n /= 10;
    }

    return n + '0';
}

constexpr intmax_t get_abs(intmax_t i)
{
    return (i < 0) ? -i : i;
}


template <char... s>
constexpr static char const char_array[] = { s..., '\0' };

template <char... s>
using char_sequence = std::integer_sequence<char, s...>;


template <intmax_t n, typename IndexSequence>
struct make_char_sequence;

template <intmax_t n, std::size_t... indices>
struct make_char_sequence<n, std::index_sequence<indices...>>
{
    using type = char_sequence<
                    get_digit_char(n, get_number_of_digit(n), sizeof...(indices) - indices)...
                 >;
};


template <char... s>
constexpr auto make_char_array(char_sequence<s...>, bool isNegative)
{
    if (isNegative) {
        return char_array<'-', s...>;
    }
    return char_array<s...>;
}

template <intmax_t n>
constexpr auto to_constexpr_str()
{
    using indices_t = std::make_index_sequence<get_number_of_digit(n)>;
    using char_array_t = typename make_char_sequence<get_abs(n), indices_t>::type;
    return make_char_array(char_array_t(), n < 0);
}


template <typename Sequence1, typename Sequence2>
struct concat_sequence;

template <char... s1, char... s2>
struct concat_sequence<char_sequence<s1...>, char_sequence<s2...>>
{
    using type = char_sequence<s1..., s2...>;
};


template <std::intmax_t Num, std::intmax_t Denom>
constexpr auto to_str(std::ratio<Num, Denom>)
{
    using num_indices_t = std::make_index_sequence<get_number_of_digit(Num)>;
    using num_char_sequence_t = typename make_char_sequence<get_abs(Num), num_indices_t>::type;

    using denom_indices_t = std::make_index_sequence<get_number_of_digit(Denom)>;
    using denom_char_sequence_t = typename make_char_sequence<get_abs(Denom), denom_indices_t>::type;

    using temp_char_array_t = typename concat_sequence<num_char_sequence_t, char_sequence<'/'>>::type;
    using final_char_array_t = typename concat_sequence<temp_char_array_t, denom_char_sequence_t>::type;

    return make_char_array(final_char_array_t(), (Num < 0 && Denom > 0) || (Num > 0 && Denom < 0));
}


int main() {
    using std::is_same;
    using std::ratio;
    using std::ratio_add;
    using std::ratio_multiply;
    using std::ratio_equal;
    using std::string;
    using std::cout;
    using std::endl;

    using two_third = ratio<2, 3>;
    cout << two_third::num << '/' << two_third::den << endl;   // 2/3

    using four_sixth = ratio<4, 6>;
    cout << four_sixth::num << '/' << four_sixth::den << endl; // 2/3

    static_assert(
            !is_same<two_third, four_sixth>::value,
            "two_third and four_sixth are not the same type."
    );
    static_assert(
            (two_third::num == four_sixth::num) && (two_third::den == four_sixth::den),
            "but two_third and four_sixth have the same numerator and denominator values."
    );
    static_assert(ratio_equal<two_third, four_sixth>::value, "two_third and four_sixth have same ratio.");

    using four_third = ratio_add<two_third, two_third>;
    static_assert(is_same<four_third, ratio<4, 3>>::value, "");
    static_assert(ratio_equal<four_third, ratio<4, 3>>::value, "");

    using eight_sixth = ratio_multiply<four_sixth, ratio<2>>;
    static_assert(is_same<eight_sixth, ratio<4, 3>>::value, ""); // reduced to the lowest terms.
    static_assert(ratio_equal<eight_sixth, ratio<4, 3>>::value, "");

    constexpr auto str = to_constexpr_str<1024>();
    cout << str << endl;
    assert(string("1024") == str);

    constexpr auto str1 = to_constexpr_str<-1024>();
    cout << str1 << endl;
    assert(string("-1024") == str1);

    constexpr auto str2 = to_constexpr_str<9876543210>();
    cout << str2 << endl;
    assert(string("9876543210") == str2);

    constexpr auto str3 = to_constexpr_str<-9876543210>();
    cout << str3 << endl;
    assert(string("-9876543210") == str3);

    constexpr auto two_third_str = to_str(two_third());
    cout << two_third_str << endl;
    assert(string("2/3") == two_third_str);

    using minus_two_third = ratio<-2, 3>;
    constexpr auto minus_two_third_str = to_str(minus_two_third());
    cout << minus_two_third_str << endl;
    assert(string("-2/3") == minus_two_third_str);

    using minus_two_third1 = ratio<2, -3>;
    constexpr auto minus_two_third_str1 = to_str(minus_two_third1());
    cout << minus_two_third_str1 << endl;
    assert(string("-2/3") == minus_two_third_str1);

    return 0;
}

