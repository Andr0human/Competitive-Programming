/*** 
 * Project Euler #2: Even Fibonacci numbers
 * Approach : Precompute Fibonacci Squence and answer query in O(1).
 * O(N) may also work.
***/

#include <bits/stdc++.h>
using namespace std;

#define yes "Yes"
#define no "No"
#define ll long long
#define ull unsigned long long
const int mod = (int)1e9 + 7;


vector<ll> preCompute() {

    ll N = (ll)4e16;
    vector<ll> arr(2);
    arr[0] = 1; arr[1] = 2;

    while (true) {
        int len = arr.size() - 1;
        arr.emplace_back(arr[len] + arr[len - 1]);
        if (arr.back() > N) break;
    }
    return arr;
}

ll mySolution(vector<ll> &arr) {

    ll N; cin >> N;
    ll res = 0;
    for (ll i : arr) {
        if (i > N) break;
        if (i & 1) continue;
        res += i;
    }

    return res;
}


int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    vector<ll> fibo = preCompute();

    int testcases; cin >> testcases;
    while(testcases--) {
        auto ans = mySolution(fibo);
        cout << ans << endl;
    }
}
