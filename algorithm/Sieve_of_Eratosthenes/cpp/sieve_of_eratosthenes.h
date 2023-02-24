#ifndef CPP_SIEVE_OF_ERATOSTHENES_H
#define CPP_SIEVE_OF_ERATOSTHENES_H


#include <vector>


namespace sieve_of_eratosthenes {
    std::vector<int> get(unsigned int upperLimitN);

    namespace detail {
        std::vector<int> simple_get(unsigned int upperLimitN);
        std::vector<int> optimized_get(unsigned int upperLimitN);
    }
} // namespace sieve_of_eratosthenes


#endif //CPP_SIEVE_OF_ERATOSTHENES_H
