/*** 
 * Project Euler #13: Large sum
 * Approach : Use string in store each number and find sum for
 * first 50 digits.
***/

#include <bits/stdc++.h>
using namespace std;

int main() {
    std::ios::sync_with_stdio(0); std::cin.tie(0);

    int N; cin >> N;
    vector<string> arr(N);
    vector<int> res;
    for (int i = 0; i < N; i++) cin >> arr[i];

    for (int j = 49; j >= 0; j--) {
        int curr = 0;
        for (int i = 0; i < N; i++)
            curr += arr[i][j] - '0';
        res.emplace_back(curr);
    }


    for (int i = 0; i < 49; i++) {
        res[i + 1] += res[i] / 10;
        res[i] %= 10;
    }

    while (res.back() > 9) {
        int x = res.back() / 10;
        res[res.size() - 1] %= 10;
        res.emplace_back(x);
    }

    for (int i = res.size() - 1; i > res.size() - 10; i--) cout << res[i];
   
}
