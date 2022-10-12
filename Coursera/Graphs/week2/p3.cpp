#include <bits/stdc++.h>
using namespace std;

#define INT_MATRIX vector<vector<int>>

vector<bool> visited;
vector<int> post_order;

INT_MATRIX
rev(const INT_MATRIX &arr)
{
    INT_MATRIX res(arr.size(), vector<int>());
    
    for (size_t i = 1; i < arr.size(); i++)
        for (int j : arr[i])
            res[j].emplace_back(i);
    return res;
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
    }
    return g;
}

void
dfs(const INT_MATRIX &g, int vertex, int &order)
{
    visited[vertex] = true;
    for (int edge : g[vertex])
        if (!visited[edge])
            dfs(g, edge, order);
    post_order[order++] = vertex;
}

void
explore(const INT_MATRIX &g, int vertex)
{
    visited[vertex] = true;
    for (int edge : g[vertex])
        if (!visited[edge])
            explore(g, edge);
}

void
scc(const INT_MATRIX &g, const INT_MATRIX &rg)
{
    const int n = g.size();
    post_order.resize(n);
    visited.resize(n);

    int order = 1;
    for (int i = 1; i < n; i++)
        if (!visited[i])
            dfs(rg, i, order);

    // print(post_order);

    for (int i = 1; i < n; i++)
        visited[i] = false;
    
    int answer = 0;
    for (int i = n - 1; i >= 1; i--)
    {
        int vertex = post_order[i];
        if (!visited[vertex])
        {
            explore(g, vertex);
            answer++;
        }
    }
    
    cout << answer << endl;
}

int main()
{    
    INT_MATRIX g = get_graph();
    INT_MATRIX rev_g = rev(g);

    scc(g, rev_g);
}

