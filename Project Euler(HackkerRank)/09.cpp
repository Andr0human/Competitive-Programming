/*** 
 * Project Euler #9: Special Pythagorean triplet
 * Approach : PreCompute all pythagorean triplets in O(N * N).
 * Iterate through the list of triplets for each query. O(N)
***/

#include <bits/stdc++.h>
using namespace std;

#define yes "Yes"
#define no "No"
#define ll long long
#define ull unsigned long long
const int mod = (int)1e9 + 7;

struct triplets {
    ll a, b, c;

    triplets(ll t1, ll t2, ll t3) {
        a = t1;
        b = t2;
        c = t3;
    }

};

ll mySolution(ll N, vector<triplets> &arr) {
    ll best = -1;
    
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i].a + arr[i].b + arr[i].c == N)
            best = max(best, arr[i].a * arr[i].b * arr[i].c);
    }

    return best;
}

vector<triplets> preprocess() {
    int maxN = 3005;

    vector<triplets> arr;

    for (ll a = 1; a <= maxN; a++) {
        for (ll b = a + 1; b <= maxN; b++) {
            if (a + b >= maxN) break;
            double c_sq = a * a + b * b;
            double c = sqrt(c_sq);
            if (a + b + floor(c) > maxN) break;
            if (floor(c) == c) arr.emplace_back(triplets(a, b, (ll)c));
        }
    }

    return arr;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    vector<triplets> arr = preprocess();

    int testcases; cin >> testcases;
    while(testcases--) {
        int N; cin >> N;
        cout << mySolution(N, arr) << endl;
    }
}
