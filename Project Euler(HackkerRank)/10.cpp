/*** 
 * Project Euler #10: Summation of primes
 * Approach : PreCompute a prime list for first 1 million primes.
 * Using precomputed list, each query can be done in O(N) Time.
***/

#include <bits/stdc++.h>
using namespace std;

#define yes "Yes"
#define no "No"
#define ll long long
#define ull unsigned long long
const int mod = (int)1e9 + 7;

std::vector <int> PrimeListupto(int N) {
    std::vector <bool> arr(N + 1, true);
    arr[0] = arr[1] = false;
    for (int i = 4; i <= N; i += 2) arr[i] = false;
    for (int i = 3; i * i <= N; i += 2) {
        if (arr[i]) {
            for (int j = i * i; j <= N; j += i) arr[j] = false;
        }
    }

    std::vector <int> ans;
    for (int i = 0; i < N; i++) {
        if (arr[i]) ans.emplace_back(i);
    }
    /// We get an array where ith is the number & arr[ith] tells if its a prime

    return ans;
}

ll mySolution(int N, vector<int> &arr) {

    ll res = 0;

    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] > N) break;
        res += arr[i];
    }

    return res;
}


int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    vector<int> primes = PrimeListupto(1000050);

    int testcases; cin >> testcases;
    while(testcases--) {
        int N; cin >> N;
        auto ans = mySolution(N, primes);
        cout << ans << endl;
    }
}
