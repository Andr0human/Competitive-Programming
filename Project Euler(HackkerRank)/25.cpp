/*** 
 * Project Euler #25: N-digit Fibonacci number
 * Approach : Precompute for each digit using BigInt Lib.
***/

#include <iostream>
#include "BigInt.h"

std::vector<int> preCompute() {
    const int maxN = 5002;
    std::vector<int> arr(maxN + 1);

    arr[1] = 1;
    BigInt prev, curr, next;
    prev = 1; curr = 1;
    int cnt = 3;

    while (true) {
        next = prev + curr;
        prev = curr;
        curr = next;
        int len = curr.len();
        if (len > maxN) break;
        if (!arr[len]) arr[len] = cnt;

        cnt++;
    }

    return arr;
}


int main() {
    std::ios::sync_with_stdio(0); std::cin.tie(0);
    auto fib = preCompute();

    int t; std::cin >> t;
    while (t--) {
        int N; std::cin >> N;
        std::cout << fib[N] << std::endl;
    }
 
}
