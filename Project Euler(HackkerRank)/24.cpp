/***
 * Project Euler #24: Lexicographic permutations
***/

#include <bits/stdc++.h>
using namespace std;

#define yes "Yes"
#define no "No"
#define ll long long
#define ull unsigned long long
const int mod = (int)1e9 + 7;

string incremented(string s, int inc) {
    while (inc--) next_permutation(s.begin(), s.end());
    return s;
}

string incremented2(string s, int i) {
    int idx = s.length() - 1 - i;
    for (int j = idx + 1; j < s.length(); j++) {
        if (s[j] > s[idx]) {
            swap(s[idx], s[j]);
            break;
        }
    }
    return s;
}

string mySolution() {

    string s = "abcdefghijklm";
    ll N, fact[15]; cin >> N;
    N--;

    for (int i = 1; i <= 14; i++)
        fact[i] = i;
    for (int i = 2; i <= 14; i++)
        fact[i] *= fact[i - 1];
    

    while (N > fact[4]) {
        int i;
        for (i = 4; i <= 13; i++) {
            if (fact[i] > N) break;
        }
        i--;
        s = incremented2(s, i);
        N -= fact[i];
    }

    s = incremented(s, N);
    return s;
}


int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int testcases; cin >> testcases;
    while(testcases--) {
        auto ans = mySolution();
        cout << ans << endl;
    }
}
