#include <bits/stdc++.h>
using namespace std;

vector<bool> visited;

void explore_and_mark(int current, int value, vector<vector<int>> &arr)
{
    for (int i : arr[current])
    {
        if (visited[i])
            continue;
        visited[i] = true;
        explore_and_mark(i, value, arr);
    }
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

    int answer = 0;
    for (int i = 1; i <= n; i++)
    {
        if (visited[i])
            continue;
        answer++;
        explore_and_mark(i, answer, points);
    }

    cout << answer;
}
