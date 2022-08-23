/*** 
 * Project Euler #5: Smallest multiple
 * Approach : Answer for N will product of all primes factors of 1 to N.
***/

#include <bits/stdc++.h>
using namespace std;

#define yes "Yes"
#define no "No"
#define ll long long
#define ull unsigned long long
const int mod = (int)1e9 + 7;

long long gcd(long long a, long long b) {
    while(b){
        a %= b;
        std::swap(a, b);
    }
    return a;
}

int mySolution(int N) {

    int res = 1;

    for (int i = 2; i <= N; i++) {
        if (res % i == 0) continue;
        int g = gcd(res, i);
        res *= i / g;
    }


    return res;
}


int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int testcases; cin >> testcases;
    while(testcases--) {
        int N; cin >> N;
        auto ans = mySolution(N);
        cout << ans << endl;
    }
}
