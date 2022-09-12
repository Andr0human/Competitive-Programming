/*** 
 * Project Euler #12: Highly divisible triangular number
 * Approach : Make a factor count function for N in O(sqrt(N)) Time.
 * Linear search for each Query. O(N) Time.
 * Overall Query Time Complexity : O(N * sqrt(N))
***/

#include <bits/stdc++.h>
using namespace std;

int factor_count (long long N) {
    int res = 1, cnt;
    if (!(N % 2)) {
        cnt = 0;
        while (!(N % 2)) {
            N >>= 1;
            cnt++;
        }
        res *= cnt + 1;
    }

    for (long long i = 3; i * i <= N; i += 2) {
        if (!(N % i)) {
            cnt = 0;
            while (!(N % i)) {
                N /= i;
                cnt++;
            }
            res *= cnt + 1;
        }
    }
    if (N > 1) res *= 2;
    
    return res;
}

long long mySolution(long long n) {
    long long _x = -1;
    for (long long i = 1;; i++) {
        _x = i * (i + 1) / 2;
        if (factor_count(_x) > n) break;
    }
    return _x;
}

int main() {
    std::ios::sync_with_stdio(0); std::cin.tie(0);

    int t; cin >> t;
    while (t--) {
        int N; cin >> N;
        cout << mySolution(N) << endl;
    }
}
