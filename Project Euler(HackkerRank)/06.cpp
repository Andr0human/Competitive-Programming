/*** 
 * Project Euler #6: Sum square difference
 * Approach : Sum of squares upto N => [(N) * (N + 1) * (2 * N + 1)] / 6
 * Sum upto N = [(N) * (N + 1)] / 2
***/

#include <bits/stdc++.h>
using namespace std;

#define yes "Yes"
#define no "No"
#define ll long long
#define ull unsigned long long
const int mod = (int)1e9 + 7;



ll mySolution() {
    ll N; cin >> N;

    ll res1 = N * (N + 1) * (2 * N + 1) / 6;
    ll res2 = N * (N + 1) / 2;
    res2 *= res2;

    return abs(res1 - res2);
}


int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int testcases; cin >> testcases;
    while(testcases--) {
        auto ans = mySolution();
        cout << ans << endl;
    }
}
