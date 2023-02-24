#include "sieve_of_eratosthenes.h"


namespace sieve_of_eratosthenes {
    std::vector<int> get(unsigned int upperLimitN) {
        return detail::simple_get(upperLimitN);
    }
}
