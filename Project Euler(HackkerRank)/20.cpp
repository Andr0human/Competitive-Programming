/***
 * Project Euler #20: 
 * Approach : Implement a BigInt class to compute factorials for large values of N,
 *            then iterate through the digits for answer
***/


#include <iostream>
#include "../lib/BigInt.h"

using std::cin;
using std::cout;

int sum_of_digits(const std::string& __s) {
    int res = 0;
    for (const auto ch : __s)
        res += static_cast<int>(ch - '0');
    return res;
}


int main() {

    int t;
    cin >> t;

    while (t--) {
        int N;
        cin >> N;
        BigInt res = 1;
        for (int i = 1; i <= N; i++)
            res *= i;
        cout << sum_of_digits(res.str()) << '\n';
    }

}

