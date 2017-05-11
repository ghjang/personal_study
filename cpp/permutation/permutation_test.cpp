#include "catch.hpp"

#include <algorithm>
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
