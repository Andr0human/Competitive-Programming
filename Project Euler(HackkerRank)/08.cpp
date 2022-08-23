/*** 
 * Project Euler #8: Largest product in a series
 * Approach : Brute Force
***/

#include <bits/stdc++.h>
using namespace std;

#define yes "Yes"
#define no "No"
#define ll long long
#define ull unsigned long long
const int mod = (int)1e9 + 7;


int mySolution() {

    int N, k; cin >> N >> k;
    string arr; cin >> arr;

    int best = 0;

    for (int i = 0; i < N - k; i++) {
        int res = 1;
        for (int j = i; j < i + k; j++)
            res *= arr[j] - '0';
        best = max(best, res);
    }

    return best;
}


int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int testcases; cin >> testcases;
    while(testcases--) {
        auto ans = mySolution();
        cout << ans << endl;
    }
}
