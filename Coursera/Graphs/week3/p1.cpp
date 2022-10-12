
#include <bits/stdc++.h>
using namespace std;

#define INT_MATRIX vector<vector<int>>

void
print_graph(vector<vector<int>> &g)
{
    for (size_t i = 0; i < g.size(); i++)
    {
        if (g[i].empty()) continue;
        cout << i << " -> ";
        for (int j : g[i]) cout << j << " ";
        cout << endl;
    }
}

INT_MATRIX
get_graph()
{
    int n, m;
    cin >> n >> m;

    INT_MATRIX g(n + 1, vector<int>());
    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        g[x].emplace_back(y);
        g[y].emplace_back(x);
    }
    return g;
}

vector<int>
bfs(INT_MATRIX g, int start)
{
    const int n = g.size();
    vector<int> dist(n, INT_MAX);

    dist[start] = 0;

    queue<int> edges;
    edges.push(start);

    while (!edges.empty())
    {
        int current = edges.front();
        edges.pop();
        for (int vertex : g[current])
        {
            if (dist[vertex] == INT_MAX)
            {
                edges.push(vertex);
                dist[vertex] = dist[current] + 1;
            }
        }
    }

    for (int &element : dist)
        if (element == INT_MAX) element = -1;

    return dist;
}

int main()
{
    auto g = get_graph();

    int start, end;
    cin >> start >> end;

    auto dist = bfs(g, start);
    // print(dist);
    cout << dist[end] << endl;
}
