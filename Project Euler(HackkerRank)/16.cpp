/***
 * Project Euler #16: Power digit sum
 * Approach : Implement a BigInt class to compute 2 ^ N for large values of N,
 *            then iterate through the digits for answer
***/


#include <iostream>
#include "../lib/BigInt.h"


int sum_of_digits(const std::string& __s) {
    int res = 0;
    for (const auto ch : __s)
        res += static_cast<int>(ch - '0');
    return res;
}

BigInt big_pow(BigInt a, int b) {
    BigInt res = 1;
    while (b) {
        if (b & 1) res *= a;
        b >>= 1;
        a *= a;
    }
    return res;
}

int main() {
    std::ios::sync_with_stdio(0); std::cin.tie(0);

    int t;
    std::cin >> t;
    while (t--) {
        int N;
        std::cin >> N;
        BigInt a = big_pow(2, N);
        std::cout << sum_of_digits(a.str()) << std::endl;
    }

}

