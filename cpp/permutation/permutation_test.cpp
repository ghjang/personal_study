#include "catch.hpp"

#include <cassert>
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


template <typename T, std::size_t N, std::size_t M>
constexpr auto term_sign(std::array<std::array<T, N>, M> const & perm)
{
    std::array<int, M> signs{};

    for (int i = 0; i < M; ++i) {
        int reverseOrderCnt = 0;
        auto & p = perm[i];
        for (int j = 0; j < N - 1; ++j) {
            for (int k = j + 1; k < N; ++k) {
                if (p[j] > p[k]) {
                    ++reverseOrderCnt;
                }
            }
        }
        signs[i] = (reverseOrderCnt % 2 == 0) ? 1 : -1;
    }

    return signs;
}

template <int M, int N, typename T>
constexpr auto det_impl(T & mat)
{
    static_assert(M == N);
    static_assert(M >= 2 && N >= 2);

    using ret_t = std::remove_const_t<
                        std::remove_reference_t<
                                decltype(mat[0][0])
                        >
                  >;

    ret_t v = 0;

    constexpr auto indices = permutation_index<N>();
    constexpr auto signs = term_sign(indices);

    // TODO: Is it possible to apply loop un-rolling by using  C++17 fold expression?
    //          std::apply & constexpr functor?
    //          need to introduce an impl object?
    for (int i = 0; i < indices.size(); ++i) {
        int term = signs[i];
        auto & p = indices[i];
        for (int j = 0; j < p.size(); ++j) {
            term *= mat[j][p[j]];
        }
        v += term;
    }

    return v;
}

template <typename T, int M, int N>
constexpr auto det(T (& mat)[M][N])
{
    return det_impl<M, N>(mat);
}

template <typename T, std::size_t N, std::size_t M>
constexpr auto det(std::array<std::array<T, N>, M> const & mat)
{
    return det_impl<M, N>(mat);
}

/*
 * NOTE: The most generic version.
 *        It will work OK only if the mat's size is M x N.
 *        And the mat should provide 'operator []' for accessing the elements.
 */
template <int M, int N, typename T>
constexpr auto det(T & mat)
{
    return det_impl<M, N>(mat);
}


TEST_CASE("det", "[permutation]")
{
    //==== C++ built-in array ====

    // compile-time calculation
    constexpr int mat[2][2] = { { 3, 0 },
                                { 0, 2 } };
    static_assert(det(mat) == 6);

    // runtime calculation
    int mat1[2][2] = { { 3, 0 },
                       { 0, 2 } };
    REQUIRE(det(mat1) == 6);

    //==== std::array ====
    using mat_t = std::array<std::array<int, 2>, 2>;

    // compile-time calculation
    constexpr mat_t mat2 = { { { 3, 0 },
                               { 0, 2 } } };
    static_assert(det(mat2) == 6);

    // runtime calculation
    mat_t mat3 = { { { 3, 0 },
                     { 0, 2 } } };
    REQUIRE(det(mat3) == 6);

    //==== std::vector ====
    std::vector<std::vector<int>> mat4{ { 3, 0 },
                                        { 0, 2 } };
    REQUIRE(mat4.size() == 2);
    REQUIRE(mat4[0][0] == 3);
    REQUIRE(mat4[0][1] == 0);
    REQUIRE(mat4[1][0] == 0);
    REQUIRE(mat4[1][1] == 2);

    // runtime calculation
    REQUIRE((det<2, 2>(mat4) == 6));
}


struct functor
{
    template <typename... Int>
    int operator () (Int... i)
    {
        return (sign_ * ... * f(i));
    }

    int f(int i)
    {
        return i * i;
    }

    int const sign_;
};

TEST_CASE("fold expression", "[permutation]")
{
    std::array<int, 5> arr;
    std::iota(arr.begin(), arr.end(), 0);

    std::apply(functor{ -1 }, arr); 
}
