/*** 
 * Project Euler #22: Names scores
 * Approach : Self-Explanatory (Brute Force)
***/

#include <bits/stdc++.h>
using namespace std;

#define yes "Yes"
#define no "No"
#define ll long long
#define ull unsigned long long
const int mod = (int)1e9 + 7;


int mySolution(vector<string> &names) {

    string person; cin >> person;

    for (int i = 0; i < names.size(); i++) {
        if (names[i] != person) continue;
        int val = 0;
        for (char ch : person) val += (ch - 'A' + 1);
        return val * (i + 1);
    }

    return 0;
}


int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int N; cin >> N;
    vector<string> names(N);
    for (int i = 0; i < N; i++) cin >> names[i];
    sort(names.begin(), names.end());

    int testcases; cin >> testcases;
    while(testcases--) {
        auto ans = mySolution(names);
        cout << ans << endl;
    }
}
