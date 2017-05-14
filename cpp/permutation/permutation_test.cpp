#include "catch.hpp"

#include <algorithm>
#include <numeric>
#include <array>
#include <string>
#include <iostream>


// NOTE: it's OK to pass std::array reference argument in constexpr contexts.
constexpr void constexpr_array_reference_argument_impl(std::array<int, 5> & arr)
{
    arr[0] = 100;
}

constexpr auto constexpr_array_reference_argument()
{
    std::array<int, 5> arr{ 0, 1, 2, 3, 4 };
    constexpr_array_reference_argument_impl(arr);
    return arr;
}

TEST_CASE("constexpr std::array reference argument", "[permutation]")
{
    // it's OK.
    constexpr auto arr = constexpr_array_reference_argument();
    static_assert(arr[0] == 100);
}


TEST_CASE("std::next_permutation", "[permutation]")
{
    std::string s = "abc";
    int cnt = 0;

    do {
        std::cout << s << '\n';
        ++cnt;
    } while (std::next_permutation(s.begin(), s.end()));
    REQUIRE("abc" == s);
    REQUIRE(6 == cnt);

    std::cout << '\n';

    s = "aba";
    cnt = 0;
    std::sort(s.begin(), s.end());

    do {
        std::cout << s << '\n';
        ++cnt;
    } while (std::next_permutation(s.begin(), s.end()));
    REQUIRE("aab" == s);
    REQUIRE(3 == cnt);
}


constexpr auto factorial(int n)
{
    int v = n;
    while (n > 1) {
        v *= --n;
    }
    return v;
}

TEST_CASE("factorial", "[permutation]")
{
    static_assert(factorial(3) == 6);
    static_assert(factorial(4) == 24);
}


void bubble_reverse(std::array<int, 0> & arr)
{
    std::copy(arr.begin(), arr.end(), std::ostream_iterator<int>(std::cout, " "));
}

void bubble_reverse(std::array<int, 1> & arr)
{
    std::copy(arr.begin(), arr.end(), std::ostream_iterator<int>(std::cout, " "));
}

template <std::size_t N>
void bubble_reverse(std::array<int, N> & arr)
{
    for (int i = 0; i < arr.size() - 1; ++i) {
        int j = arr.size() - 2;
        int k = arr.size() - 1;
        for ( ; j >= i; --j, --k) {
            std::swap(arr[j], arr[k]);
            std::copy(arr.begin(), arr.end(), std::ostream_iterator<int>(std::cout, " "));
            std::cout << '\n';
        }
    }
}

TEST_CASE("bubble_reverse", "[permutation]")
{
    std::cout << "==== bubble_reverse\n";
    std::array<int, 5> arr{ 0, 1, 2, 3, 4 };
    std::copy(arr.begin(), arr.end(), std::ostream_iterator<int>(std::cout, " "));
    bubble_reverse(arr);
}


template <std::size_t N1, std::size_t N2>
void permutation_index_impl(std::array<int, N1> seq, int i, int j,
                            std::array<std::array<int, N1>, N2> & out,
                            int & cnt)
{
    if (i == j) {
        std::cout << "temp1: ";
        std::copy(seq.begin(), seq.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << '\n';
        return;
    }

    int k = i;
    int l = i + 1;
    for ( ; l <= j; ++l) {
        permutation_index_impl(seq, i + 1, j, out, cnt);

        std::swap(seq[k], seq[l]);

        std::cout << "temp2: ";
        std::copy(seq.begin(), seq.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << '\n';
    }
}

template <int N>
auto permutation_index()
{
    static_assert(N > 0);

    using seq_t = std::array<int, N>;

    seq_t seq;
    std::iota(seq.begin(), seq.end(), 0);

    constexpr auto numOfPerm = factorial(N);
    std::array<seq_t, numOfPerm * 2> indices{};
    int cnt = 0;

    permutation_index_impl(seq, 0, seq.size() - 1, indices, cnt);

    return indices;
}

template <typename T>
struct TD;

TEST_CASE("permutation_index", "[permutation]")
{
    /*
    std::cout << "==== perm-1:\n";
    auto i1 = permutation_index<1>();
    for (auto & p : i1) {
        std::copy(p.begin(), p.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << '\n';
    }

    std::cout << "==== perm-2:\n";
    auto i2 = permutation_index<2>();
    for (auto & p : i2) {
        std::copy(p.begin(), p.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << '\n';
    }
    */

    std::cout << "==== perm-2:\n";
    auto i3 = permutation_index<3>();

    /*
    for (auto & p : i3) {
        std::copy(p.begin(), p.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << '\n';
    }
    */
}


template <std::size_t N>
bool print_permutation_index_impl(std::array<int, N> arr, int i)
{
    if (i == N - 1) {
        std::copy(arr.begin(), arr.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << '\n';
        return false;
    }

    for (int j = i + 1; j <= N; ++j) {
        if (print_permutation_index_impl(arr, i + 1)) {
            std::swap(arr[i], arr[j]);
        }
    }

    return true;
}

template <std::size_t N>
void print_permutation_index()
{
    std::array<int, N> arr{};
    std::iota(arr.begin(), arr.end(), 0);
    print_permutation_index_impl(arr, 0);
}

TEST_CASE("print_permutation_index", "[permutation]")
{
    std::cout << "//==== print_permutation_index\n";
    print_permutation_index<4>();
}
