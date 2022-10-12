#include "../../../lib/templates.h"
#define FAST_IO ios::sync_with_stdio(0); cin.tie(0);
#define INT_MATRIX vector<vector<int>>

const int INF = 1e8;
map<pair<int, int>, int> edge_cost;

INT_MATRIX
get_graph()
{
    int n, m;
    cin >> n >> m;

    INT_MATRIX g(n + 1, vector<int>());
    for (int i = 0; i < m; i++)
    {
        int x, y, cost;
        cin >> x >> y >> cost;
        g[x].emplace_back(y);
        edge_cost[make_pair(x, y)] = cost;
    }
    return g;
}

vector<int>
bellman_floyd(INT_MATRIX &g, int src)
{
    const size_t n = g.size();
    vector<int> dist(n, INF);
    dist[src] = 0;

    for (size_t i = 0; i < n - 1; i++)
    {
        for (size_t vt = 1; vt < n; vt++)
        {
            if (dist[vt] == INF) continue;
            for (auto edge : g[vt])
            {
                int newDist = dist[vt] + edge_cost[make_pair(vt, edge)];
                if (newDist < dist[edge])
                    dist[edge] = newDist;
            }
        }
    }

    for (size_t i = 0; i < n - 1; i++)
    {
        for (size_t vt = 1; vt < n; vt++)
        {
            if (dist[vt] == INF) continue;
            for (auto edge : g[vt])
            {
                if (dist[vt] + edge_cost[make_pair(vt, edge)] < dist[edge])
                    dist[edge] = -INF;
            }
        }
    }

    return dist;
}

bool
solve(vector<int> &dist)
{
    for (size_t i = 1; i < dist.size(); i++)
        if (dist[i] == -INF)
            return true;
    return false;
}

int main()
{
    FAST_IO

    auto g = get_graph();
    auto dist = bellman_floyd(g, 1);

    cout << solve(dist);
}


