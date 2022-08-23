/*** Project Euler #15: Lattice paths
 * Approach : Using Combinatorics, if (N for right) and (M for down) then,
 * total ways = (N + M)Cn or (N + M)Cm
***/

#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll mod = (int)1e9 + 7;


int gcd(int a, int b) {
    while(b){
        a %= b;
        std::swap(a, b);
    }
    return a;
}

ll nCr(int n, int r) {
    ll res = 1;

    // Not the most efficient way to calculate NCr but will work for problem

    vector<int> A, B;
    for (int i = n; i > n - r; i--) A.emplace_back(i);
    for (int i = 2; i <= r; i++) B.emplace_back(i);

    for (int i = 0; i < B.size(); i++) {
        for (int j = 0; j < A.size(); j++) {
            int g = gcd(A[j], B[i]);
            if (g > 1) {
                B[i] /= g;
                A[j] /= g;
            }
            if (B[i] == 1) break;
        }
    }    

    for (int i = 0; i < A.size(); i++)
        res = (ll)(res * A[i]) % mod;
    return res;
}

int main() {
    std::ios::sync_with_stdio(0); std::cin.tie(0);

    int t; cin >> t;
    while (t--) {
        int N, M; cin >> N >> M;
        cout << nCr(N + M, min(N, M)) << endl;
    }

}
