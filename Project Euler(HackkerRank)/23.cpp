/***
 * Project Euler #23: Non-abundant sums
 * Approach : Brute Force with preprocessing
***/

#include <bits/stdc++.h>
using namespace std;

#define yes "YES"
#define no "NO"
#define ll long long
#define ull unsigned long long
const int mod = (int)1e9 + 7;
const int maxN = (int)3e4 + 1;

int factors_sum (int N) {
    std::vector<int> factors = {1, N};
    int res = 1;
    for (int i = 2; i * i <= N; i++) {
        if (!(N % i)) {
            int d = N / i;
            res += i;
            if (d != i) res += d;
        }
    }
    return res;
}

string mySolution(int N, vector<int> &list) {
    if (N > 28123) return yes;

    for (int i = 0; i < list.size(); i++) {
        for (int j = i; j < list.size(); j++)
            if (list[i] + list[j] == N) return yes;
    }


    return no;
}


vector<int> abundant_number_list() {
    vector<int> arr;
    for (int i = 1; i <= maxN; i++)
        if (factors_sum(i) > i) arr.emplace_back(i);
    return arr;
}


int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    auto arr = abundant_number_list();

    int testcases; cin >> testcases;
    while(testcases--) {
        int N; cin >> N;
        auto ans = mySolution(N, arr);
        cout << ans << endl;
    }
}
