#include <bits/stdc++.h>
using namespace std;

#define INT_MATRIX vector<vector<int>>

vector<int> visited;

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

void
explore(INT_MATRIX &g, int src)
{
    for (int edge : g[src])
    {
        if (visited[edge] != -1)
            continue;
        visited[edge] = visited[src] ^ 1;
        explore(g, edge);
    }
}

bool
is_bi_partite(INT_MATRIX g)
{
    visited.resize(g.size(), -1);
    for (size_t i = 1; i < g.size(); i++)
    {
        if (visited[i] != -1)
            continue;
        visited[i] = 1;
        explore(g, i);
    }

    for (size_t i = 1; i < g.size(); i++)
        for (int edge : g[i])
            if (!(visited[i] ^ visited[edge]))
                return false;

    return true;
}

int main()
{
    auto g = get_graph();
    bool x = is_bi_partite(g);
    
    cout << x << endl;
    // print(visited);
}
