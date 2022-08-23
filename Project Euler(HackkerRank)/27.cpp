/***
 * Project Euler #27: Quadratic primes
 * Approach : Make a is_prime function that works in O(sqrt(N))
 * Brute Force for each testcase.
***/

#include <bits/stdc++.h>
using namespace std;

#define yes "Yes"
#define no "No"
#define ll long long
#define ull unsigned long long
const int mod = (int)1e9 + 7;
const int maxN = (int)1e2;

bool is_prime(long long N) {
    if (N <= 1) return false;
    if (N % 2 == 0) return false;
    for (ll i = 3; i * i <= N; i += 2)
        if (N % i == 0) return false;
    return true;
}

int primeCount(ll N, ll a, ll b) {

    int res = 0;
    for (ll i = 0;; i++) {
        ll x = (ll)i * i + a * i + b;
        if (is_prime(x)) res++;
        else break;
    }

    return res;
}

void mySolution(int N) {

    pair<int, int> best = make_pair(0, 0);
    int best_res = 0;

    for (int i = -N; i <= N; i++) {
        for (int j = -N; j <= N; j++) {
            int x = primeCount(N, i, j);
            if (x > best_res) {
                best_res = x;
                best = make_pair(i, j);
            }
        }
    }

    std::cout << best.first << " " << best.second;

}


int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int N; cin >> N;
    mySolution(N);

}
