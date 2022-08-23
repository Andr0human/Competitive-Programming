/***
 * Project Euler #18: Maximum path sum I
 * Approach : Use Recursion to search all paths (No memoization needed)
***/

#include <bits/stdc++.h>
using namespace std;

#define yes "Yes"
#define no "No"
#define ll long long
#define ull unsigned long long
const int mod = (int)1e9 + 7;

template<typename T> void read(vector<vector<T>> &arr) {
    for (int i = 0; i < arr.size(); i++) for (int j = 0; j < arr[i].size(); j++) cin >> arr[i][j];
}

int search(vector<vector<int>> &arr, int j = 0, int i = 0) {
    if (i == arr.size()) return 0;
    return arr[i][j] + max(search(arr, j, i + 1), search(arr, j + 1, i + 1));
}


int mySolution() {

    int N; cin >> N;
    vector<vector<int>> arr(N, vector<int>());
    for (int i = 1; i <= N; i++) arr[i - 1].resize(i);
    read(arr);

    return search(arr);
}


int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int testcases; cin >> testcases;
    while(testcases--) {
        auto ans = mySolution();
        cout << ans << endl;
    }
}
