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


template <std::size_t N>
void print_permutation_index_impl(std::array<int, N> arr, int i)
{
    if (i == N - 1) {
        std::copy(arr.begin(), arr.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << '\n';
        return;
    }

    for (int j = i + 1, k = N - i; k > 0; ++j, --k) {
        print_permutation_index_impl(arr, i + 1);
        std::swap(arr[i], arr[j]);
    }
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
    print_permutation_index<3>();
}


template <std::size_t N, int i, std::size_t M>
constexpr void permutation_index_impl(std::array<int, N> arr,
                                      std::integral_constant<int, i>,
                                      std::array<std::array<int, N>, M> & indices,
                                      int & cnt)
{
    if constexpr (i == N - 1) {
        indices[cnt++] = arr;
    } else {
        int j = i + 1;
        for (int k = N - i; k > 0; --k) {
            permutation_index_impl(arr, std::integral_constant<int, i + 1>{}, indices, cnt);
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            if (j + 1 == N) {
                j = i;
            } else {
                ++j;
            }
        }
    }
}

template <int N>
constexpr auto permutation_index()
{
    static_assert(N > 0);

    using arr_t = std::array<int, N>;

    arr_t arr{};
    for (int i = 0; i < arr.size(); ++i) {
        arr[i] = i;
    }

    constexpr auto numOfPerm = factorial(N);
    std::array<arr_t, numOfPerm> indices{};
    int cnt = 0;

    permutation_index_impl(arr, std::integral_constant<int, 0>{}, indices, cnt);

    return indices;
}


TEST_CASE("permutation_index", "[permutation]")
{
    std::cout << "==== permutation_index\n";

    constexpr auto indices = permutation_index<4>();

    for (auto & p : indices) {
        std::copy(p.begin(), p.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << '\n';
    }
}


template <std::size_t N, typename T>
constexpr auto term_sign(T & perm)
{
    int reverseOrderCnt = 0;
    for (int i = 0; i < N - 1; ++i) {
        for (int j = i + 1; j < N; ++j) {
            if (perm[i] > perm[j]) {
                ++reverseOrderCnt;
            }
        }
    }
    return (reverseOrderCnt % 2 == 0) ? 1 : -1;
}

template <typename T, int M, int N>
constexpr auto det(T (& mat)[M][N])
{
    static_assert(M == N);
    static_assert(M >= 2 && N >= 2);

    std::remove_const_t<T> v = 0;

    constexpr auto indices = permutation_index<N>();
    for (auto & p : indices) {
        int term = term_sign<N>(p);
        for (int i = 0; i < p.size(); ++i) {
            term *= mat[i][p[i]];
        }
        v += term;
    }

    return v;
}

TEST_CASE("det", "[permutation]")
{
    constexpr int mat[][2] = { { 3, 0 },
                               { 0, 2 } };

    static_assert(det(mat) == 6);
}
