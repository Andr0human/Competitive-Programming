/*** 
 * Project Euler #3: Largest prime factor
 * Approach : Make a is_prime function that works in O(sqrt(N))
 * Check the primes for sqrt(N) values
***/

#include <bits/stdc++.h>
using namespace std;

#define yes "Yes"
#define no "No"
#define ll long long
#define ull unsigned long long
const int mod = (int)1e9 + 7;

bool is_prime(long long N) {
    if (N % 2 == 0) return false;
    for (ll i = 3; i * i <= N; i += 2)
        if (N % i == 0) return false;
    return true;
}

ll mySolution(ll N) {

    ll res = 0;
    if (is_prime(N)) return N;

    for (ll i = 2; i * i <= N; i++) {
        if (N % i == 0) {
            if (is_prime(i)) res = max(res, i);
            if (is_prime(N / i)) res = max(res, N / i);
        }
    }

    return res;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int testcases; cin >> testcases;
    while(testcases--) {
        ll N; cin >> N;
        auto ans = mySolution(N);
        cout << ans << endl;
    }
}
