/***
 * Project Euler #21: Amicable numbers
 * Approach : Precompute all amicable numbers (26 in total) and linear search for each query
***/

#include <bits/stdc++.h>
using namespace std;

#define yes "Yes"
#define no "No"
#define ll long long
#define ull unsigned long long
const int mod = (int)1e9 + 7;
const int maxN = (int)1e5 + 5;

std::vector<int> factors_of (int N, bool sorted = true) {

    std::vector<int> factors = {1};
    for (long long i = 2; i * i <= N; i++) {
        if (!(N % i)) {
            int d = N / i;
            factors.emplace_back((int)i);
            if (d != i) factors.emplace_back(d);
        }
    }
    if (sorted) sort(factors.begin(), factors.end());
    return factors;
}

int sum_of(vector<int> &arr) {
    int res = 0;
    for (int i : arr) res += i;
    return res;
}

int mySolution(int N, vector<pair<int, int>> &arr) {

    int res = 0;
    for (auto i : arr) {
        if (i.second <= N) res += i.first + i.second;
        else if (i.first <= N) res += i.first;
        else break;
    }

    return res;
}

vector<pair<int, int>> precompute() {
    vector<pair<int, int>> res;
    for (int i = 200; i <= maxN; i++) {
        vector<int> f = factors_of(i, false);
        int _x = sum_of(f);
        if (_x > i) {
            f = factors_of(_x, false);
            if (sum_of(f) == i) {
                res.emplace_back(make_pair(i, _x));
            }
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    auto arr = precompute();
    for (auto i : arr) cout << i.first << " " << i.second << endl;
    cout << "size : " << arr.size() << endl;

    int testcases; cin >> testcases;
    while(testcases--) {
        int N; cin >> N;
        auto ans = mySolution(N, arr);
        cout << ans << endl;
    }
}
