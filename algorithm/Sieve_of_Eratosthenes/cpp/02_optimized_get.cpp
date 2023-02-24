#include <cmath>

#include <catch2/catch_test_macros.hpp>


namespace sieve_of_eratosthenes::detail {
    std::vector<int> optimized_get(uint upperLimitN) {
        std::vector<bool> numbers(upperLimitN, true);

        numbers[0] = false;   // '0' is not a prime number.
        numbers[1] = false;   // '1' is not a prime number.

        int const midLimitN = static_cast<int>(std::sqrt(upperLimitN));

        for (int nextPrime = 2; nextPrime < midLimitN; ++nextPrime) {
            // move to the next prime number.
            for (int j = nextPrime; j < upperLimitN; ++j) {
                if (numbers[j]) {
                    nextPrime = j;
                    break;
                }
            }

            // mark all multiples of the current prime number as non-prime.
            for (int j = nextPrime + 1; j < upperLimitN; ++j) {
                if (numbers[j] && (j % nextPrime == 0)) {
                    numbers[j] = false;
                }
            }
        }

        std::vector<int> primes;

        for (int i = 2; i < upperLimitN; ++i) {
            if (numbers[i]) {
                primes.push_back(i);
            }
        }

        return primes;
    }
} // namespace sieve_of_eratosthenes
