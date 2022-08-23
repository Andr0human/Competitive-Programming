/*** 
 * Project Euler #11: Largest product in a grid
 * Approach : Brute Force for each direction.
***/

#include <bits/stdc++.h>
using namespace std;


void Solve(vector<vector<int>> &arr) {
    int H = arr.size(), W = arr[0].size();
    long long best = 0;

    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            long long res = 1;
            if (i + 3 < H && j + 3 < W) {
                res = 1;
                for (int x = i, y = j; x < i + 4; x++, y++) res *= arr[x][y];
                best = max(best, res);
            }

            if (i - 3 >= 0 && j + 3 < W) {
                res = 1;
                for (int x = i, y = j; y < j + 4; x--, y++) res *= arr[x][y];
                best = max(best, res);
            }

            if (i + 3 < H) {
                res = 1;
                for (int x = i, y = j; x < i + 4; x++) res *= arr[x][y];
                best = max(best, res);
            }

            if (j + 3 < W) {
                res = 1;
                for (int x = i, y = j; y < j + 4;y++) res *= arr[x][y];
                best = max(best, res);
            }
        }
    }

    cout << best;
}

int main() {
    std::ios::sync_with_stdio(0); std::cin.tie(0);

    vector<vector<int>> arr(20, vector<int>(20));

    for (int i = 0; i < arr.size(); i++)
        for (int j = 0; j < arr[0].size(); j++) cin >> arr[i][j];

    Solve(arr);
}
