/*** 
 * Project Euler #1: Multiples of 3 and 5
 * Approach : Formula for sum of AP series can give ans in O(1) time.
 * if a_first is first value and a_last is last value in AP of diff (d)
 * Then, no of term N = (a_last - a_first) / d + 1
 * Sum of Series = (a_first + a_last) / 2 * N
***/

#include <bits/stdc++.h>
using namespace std;

#define yes "Yes"
#define no "No"
#define ll long long
#define ull unsigned long long
const int mod = (int)1e9 + 7;

ll ap_sum(ll s, ll e) {
    ll d = s;
    e = floorl(e / d);
    e *= d;
    ll cnt = ((e - s) / d) + 1;
    return (e + s) * (cnt) / 2;
}

ll mySolution() {
    ll N; cin >> N;
    N--;
    // Multiples of 15 will repeat 1 extra time because of both multiple of 3 and 5
    // Thus, Sum of all multiples of (3 and 5) - sum of multiples of 15
    return ap_sum(3, N) + ap_sum(5, N) - ap_sum(15, N);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int testcases; cin >> testcases;
    while(testcases--) {
        auto ans = mySolution();
        cout << ans << endl;
    }
}
