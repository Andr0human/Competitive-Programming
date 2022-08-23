/*** 
 * Project Euler #7: 10001st prime
 * Approach : Precomputation for prime list upto nearly 500'010
***/

#include <bits/stdc++.h>
using namespace std;

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

int main() {
    std::ios::sync_with_stdio(0); std::cin.tie(0);

    int maxN = (int)5e5 + 10;
    auto arr = PrimeListupto(maxN);

    int t; cin >> t;
    while (t--) {
        int N; cin >> N;
        cout << arr[N - 1] << endl;
    }


}
