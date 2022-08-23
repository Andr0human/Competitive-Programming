/***
 * Project Euler #16: Power digit sum
 * Approach : Implement a BigInt class to compute 2 ^ N for large values of N,
 *            then iterate through the digits for answer
***/


#include <iostream>
#include "BigInt.h"


int main() {
    std::ios::sync_with_stdio(0); std::cin.tie(0);

    int t; std::cin >> t;
    while (t--) {
        int N; std::cin >> N;
        BigInt a;
        a = bigpow(2, N);
        std::cout << a.sum_of_digits() << std::endl;
    }

}

