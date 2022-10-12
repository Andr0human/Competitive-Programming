#include <bits/stdc++.h>
using namespace std;

#define FAST_IO ios::sync_with_stdio(0); cin.tie(0);
#define INT_MATRIX vector<vector<int>>
#define INT_PAIR pair<int, int>


map<INT_PAIR, int> edge_cost;

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
dijkstra(INT_MATRIX &g, int src)
{
    const size_t n = g.size();
    vector<int> dist(n, INT_MAX);
    vector<bool> visited(n, false);

    dist[src] = 0;

    auto cmp = [](INT_PAIR a, INT_PAIR b)
    { return a.second > b.second; };


    priority_queue <INT_PAIR, vector<INT_PAIR>, decltype(cmp)>  pq(cmp);
    pq.push(make_pair(src, 0));

    while (!pq.empty())
    {
        auto v = pq.top();
        pq.pop();
        
        int index = v.first, min_value = v.second;
        visited[index] = true;

        if (dist[index] < min_value)
            continue;

        for (auto e : g[index])
        {
            if (visited[e]) continue;
            int new_dist = dist[index] + edge_cost[make_pair(index, e)];
            if (new_dist < dist[e])
            {
                dist[e] = new_dist;
                pq.push(make_pair(e, new_dist));
            }
        }
    }

    for (auto &el : dist)
        if (el == INT_MAX) el = -1;

    return dist;
}


int main()
{
    auto g = get_graph();

    int start, end;
    cin >> start >> end;

    auto dist = dijkstra(g, start);
    cout << dist[end] << endl;
}
