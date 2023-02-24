#include <vector>
#include <iostream>


int main() {
    int const n = 100;

    std::vector<bool> v(n, true);

    v[0] = false;   // '0' is not a prime number.
    v[1] = false;   // '1' is not a prime number.

    for (int i = 2; i < n; ++i) {
        // move to the next prime number.
        for (int j = i; j < n; ++j) {
            if (v[j]) {
                i = j;
                break;
            }
        }

        // mark all multiples of the current prime number as non-prime.
        for (int j = i + 1; j < n; ++j) {
            if (j % i == 0) {
                v[j] = false;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        if (v[i]) {
            std::cout << i << " ";
        }
    }

    return 0;
}
