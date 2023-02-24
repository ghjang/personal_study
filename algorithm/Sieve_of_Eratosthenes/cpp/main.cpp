#include <catch2/catch_test_macros.hpp>

#include "sieve_of_eratosthenes.h"


TEST_CASE("Sieve of Eratosthenes", "[detail][simple_get]" ) {
    auto primes = sieve_of_eratosthenes::detail::simple_get(100);

    decltype(primes) expectedPrimes = {
            2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97
    };

    REQUIRE(primes == expectedPrimes);
}

TEST_CASE("Sieve of Eratosthenes", "[detail][optimized_get]" ) {
    using namespace sieve_of_eratosthenes::detail;
    REQUIRE(simple_get(100) == optimized_get(100));
    REQUIRE(simple_get(150) == optimized_get(150));
    REQUIRE(simple_get(200) == optimized_get(200));
    REQUIRE(simple_get(777) == optimized_get(777));
    REQUIRE(simple_get(1000) == optimized_get(1000));
}
