/***
 * Project Euler #20: 
 * Approach : Implement a BigInt class to compute factorials for large values of N,
 *            then iterate through the digits for answer
***/


#include <iostream>
#include "BigInt.h"



int main() {
    int t; std::cin >> t;
    while (t--) {
        int N; std::cin >> N;
        BigInt res;
        res = 1;
        for (int i = 1; i <= N; i++) res *= i;
        std::cout << res.sum_of_digits() << std::endl;
    }

}

