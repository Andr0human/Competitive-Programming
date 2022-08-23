/*** 
 * Project Euler #4: Largest palindrome product
 * Approach : PreCompute all pallindrome numbers between 101'101 and 1'000'000.
 * Check for the best value in precomputed list for each query.
***/

#include <bits/stdc++.h>
using namespace std;

#define yes "Yes"
#define no "No"
#define ll long long
#define ull unsigned long long
const int mod = (int)1e9 + 7;

template<typename T> std::vector<T> remove_duplicates(vector<T> arr) {
    if (!arr.size()) return std::vector<T>();
    sort(arr.begin(), arr.end());
    std::vector<T> res(1, arr[0]);
    for (size_t i = 1; i < arr.size(); i++) if (res.back() != arr[i]) res.emplace_back(arr[i]);
    return res;
}

bool is_pallin(int N) {
    int a0 = N % 10, a5 = (N / 100000) % 10;
    int a2 = (N / 100) % 10, a3 = (N / 1000) % 10;
    int a1 = (N / 10) % 10, a4 = (N / 10000) % 10;
    if (a0 != a5) return false;
    if (a1 != a4) return false;
    if (a2 != a3) return false;
    return true;
}

int mySolution(vector<int> &arr) {

    int N; cin >> N;
    int res = 101101;
    for (int i = 0; i < N; i++) {
        if (arr[i] >= N) break;
        res = arr[i];
    }

    return res;
}

vector<int> pallinList() {
    int N = 1000;
    vector<int> res;
    int lower = 101100, higher = 1000000;

    for (int i = 101; i < N; i++) {
        for (int j = i; j < N; j++) {
            int val = i * j;
            if (lower < val && val < higher & is_pallin(val))
                res.emplace_back(val);
        }
    }
    sort(res.begin(), res.end());
    res = remove_duplicates(res);
    return res;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    auto plist = pallinList();
    int testcases; cin >> testcases;
    while(testcases--) {
        auto ans = mySolution(plist);
        cout << ans << endl;
    }
}
