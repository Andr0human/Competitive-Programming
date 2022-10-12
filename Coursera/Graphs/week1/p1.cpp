#include <bits/stdc++.h>
using namespace std;

vector<bool> visited;

bool explore(int start, int end, vector<vector<int>> &arr)
{
    if (start == end)
        return true;
    for (int i : arr[start])
    {
        if (visited[i])
            continue;
        visited[i] = true;
        if (explore(i, end, arr))
            return true;
    }
    return false;
}

int main()
{
    int n, m, x, y;
    cin >> n >> m;

    visited.resize(n + 1, false);
    vector<vector<int>> points(n + 1, vector<int>());

    for (int i = 0; i < m; i++)
    {
        cin >> x >> y;
        points[x].emplace_back(y);
        points[y].emplace_back(x);
    }

    for (const auto &vec : points)
    {
        for (const auto value : vec)
            cout << value << ' ';
        cout << endl;
    }
}
