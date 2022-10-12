
#include "../../../lib/templates.h"
#define INT_MATRIX vector<vector<int>>


const int64_t INF = 1e16;
map<pair<int, int>, int64_t> edge_cost;

INT_MATRIX
get_graph()
{
    int n, m;
    cin >> n >> m;

    INT_MATRIX g(n + 1, vector<int>());
    for (int i = 0; i < m; i++) {
        int x, y, cost;
        cin >> x >> y >> cost;
        g[x].emplace_back(y);
        edge_cost[make_pair(x, y)] = cost;
    }
    return g;
}

vector<int64_t>
bellman_floyd(INT_MATRIX &g, int src)
{
    const int V = g.size() - 1;

    vector<int64_t> dist(V + 1, INF);
    dist[src] = 0;

    for (int i = 0; i < V - 1; i++)
    {
        for (int vt = 1; vt <= V; vt++)
        {
            if (dist[vt] == INF) continue;
            for (auto edge : g[vt])
            {
                auto vt_edge = make_pair(vt, edge);
                int64_t newDist = dist[vt] + edge_cost[vt_edge];
                if (newDist < dist[edge])
                    dist[edge] = newDist;
            }
        }
    }

    for (int i = 0; i < V - 1; i++)
    {
        for (int vt = 1; vt <= V; vt++)
        {
            if (dist[vt] == INF) continue;
            for (auto edge : g[vt])
            {
                auto vt_edge = make_pair(vt, edge);
                if (dist[vt] + edge_cost[vt_edge] < dist[edge])
                    dist[edge] = -INF;
            }
        }
    }

    return dist;
}


void
print_answer(vector<int64_t> &dist)
{
    const int n = dist.size();
    for (int i = 1; i < n; i++) {
        if (dist[i] == INF)
            cout << "*\n";
        else if (dist[i] == -INF)
            cout << "-\n";
        else
            cout << dist[i] << '\n';
    }
}

int main()
{
    auto g = get_graph();
    int src;
    cin >> src;
    auto dist = bellman_floyd(g, src);

    print_answer(dist);
}


/* 10 13
7 8 -50
8 9 -10
2 7 60
6 7 5
6 9 50
1 2 5
2 6 30
2 3 20
6 5 25
3 4 10
4 3 -15
3 5 75
5 10 100
1 */

