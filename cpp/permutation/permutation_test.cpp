#include "catch.hpp"

#include <algorithm>
#include <numeric>
#include <array>
#include <string>
#include <iostream>


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


constexpr auto factorial(unsigned char n)
{
    unsigned char v = n;
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


template <unsigned char N>
auto permutation_index()
{
    static_assert(N > 0);

    using seq_t = std::array<unsigned char, N>;

    using stack_elem_t = std::pair<
                                unsigned char,  // base index
                                unsigned char   // index of an element to swap
                         >;

    std::array<stack_elem_t, N> stack{ std::make_pair(0, 0), };
    unsigned char sp{ 0 };

    seq_t seq;
    std::iota(seq.begin(), seq.end(), 0);

    unsigned char cnt = 0;
    constexpr auto num_of_perm = factorial(N);
    std::array<seq_t, num_of_perm> indices{};

    while (cnt < num_of_perm) {
        if (sp < N - 1) {
            auto nextBaseIndex = std::get<0>(stack[sp]) + 1;
            stack[++sp] = std::make_pair(nextBaseIndex, nextBaseIndex);
        }
        else {
            std::copy(seq.begin(), seq.end(), indices[cnt++].begin());
        }
    }

    return indices;
}

template <typename T>
struct TD;

TEST_CASE("permutation_index", "[permutation]")
{
    auto i1 = permutation_index<1>();

    for (auto & p : i1) {
        for (int e : p) {
            std::cout << e << ' ';
        }
        std::cout << '\n';
    }

    //auto i2 = permutation_index<2>();
    //auto i3 = permutation_index<3>();
}
